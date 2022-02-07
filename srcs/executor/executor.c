/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/07 10:42:02 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	waitpid_fork(t_fork_list *forks, t_utils utils, int *last_pid)
{
	int			status;
	t_fork_list	*tmp;

	*last_pid = utils.last_pid;
	ft_free_char_array(utils.path_env);
	while (forks->next)
	{
		waitpid(forks->child, &status, 0);
		tmp = forks;
		forks = forks->next;
		free(tmp);
	}
	waitpid(forks->child, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return ;
}

static void	child_fork(t_cmd *cmd, t_utils *utils, int *end, int fd)
{
	int	input;
	int	output;
	
	close(end[0]);
	input = arrange_input(cmd, &utils->last_pid);
	if (input == -1)
		input = fd;
	output = arrange_output(cmd, &utils->last_pid);
	if (output == -1)
	{
		if (cmd->next)		
			output = end[1];
		else
			output = 1;
	}
	if (dup2(input, STDIN_FILENO) < 0)
		perror("");
	if (dup2(output, STDOUT_FILENO) < 0)
		perror("");
	close(end[1]);
	execute_cmd(cmd, utils);
}

static int	handle_fork(t_fork_list *a_fork, t_cmd *cmd, t_utils *utils, int fd)
{
	int		end[2];

	if (pipe(end) == -1)
	{
		perror("");
		exit(errno);
	}
	if (a_fork->child < 0)
	{
		perror("");
		exit(errno);
	}
	else if (a_fork->child == 0)
		child_fork(cmd, utils, end, fd);
	close(end[1]);
	return (end[0]);
}

static t_fork_list	*new_fork(t_fork_list *a_fork)
{
	t_fork_list	*new_fork;
	
	new_fork = (t_fork_list *)malloc(sizeof(t_fork_list));
	ft_check_malloc(new_fork, "new_fork");
	if (!a_fork)
		a_fork = new_fork;
	else
	{
		a_fork->next = new_fork;
		a_fork = a_fork->next;
	}
	return (a_fork);
}

void	executor(t_cmd *cmd, char **env, int *last_pid)
{
	t_fork_list	*a_fork;
	t_fork_list	*head_fork_list;
	int			fd;
	bool		first_cmd;
	t_utils		utils;
	
	a_fork = NULL;
	first_cmd = true;
	while (cmd)
	{
		a_fork = new_fork(a_fork);
		if (first_cmd == true)
		{
			utils = init_utils(env, last_pid);
			head_fork_list = a_fork;
			first_cmd = false;			
		}
		a_fork->child = fork();
		fd = handle_fork(a_fork, cmd, &utils, fd);
		cmd = cmd->next;
	}
	waitpid_fork(head_fork_list, utils, last_pid);
}
