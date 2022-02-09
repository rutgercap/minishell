/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:10 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/09 13:55:10 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	waitpid_fork(t_fork *forks, t_mini_vars vars)
{
	int			status;
	t_fork	*tmp;

	while (forks->next)
	{
		waitpid(forks->child, &status, 0);
		tmp = forks;
		forks = forks->next;
		free(tmp);
	}
	waitpid(forks->child, &status, 0);
	if (WIFEXITED(status))
		*vars.last_pid = WEXITSTATUS(status);
}

static void	child_fork(t_cmd *cmd, t_mini_vars *utils, int *end, int fd)
{
	int	input;
	int	output;
	
	close(end[0]);
	input = arrange_input(cmd, fd, &utils->last_pid);
	if (input != -1)
	{
		if (dup2(input, STDIN_FILENO) < 0)
			perror("");
		close(input);
	}
	output = arrange_output(cmd, end[1], &utils->last_pid);
	if (output != -1)
	{
		if (dup2(output, STDOUT_FILENO) < 0)
			perror("");
	}
	close(end[1]);
	execute_cmd(cmd, utils);
}

static int	handle_fork(t_fork *a_fork, t_cmd *cmd, t_mini_vars *utils, int fd)
{
	int		end[2];

	if (pipe(end) == -1)
	{
		perror("");
		exit(errno);
	}
	a_fork->child = fork();
	if (a_fork->child < 0)
	{
		perror("");
		exit(errno);
	}
	else if (a_fork->child == 0)
		child_fork(cmd, utils, end, fd);
	else if (a_fork->child > 0)
		close(end[1]);
	return (end[0]);
}

t_fork	*want_sum_furk(t_cmd *cmd, t_mini_vars vars)
{
	t_fork	*forks;

	forks = new_fork(NULL);
	while (cmd)
	{
		
		if (cmd->next)
		{
			forks->next = new_fork(NULL);
			forks = forks->next;
		}
		cmd = cmd->next;
	}
	return (forks);
}

void	executor(t_cmd *cmd, t_mini_vars vars)
{
	t_fork	*forks;
	
	if (vars.paths)
		vars.paths = ft_free_char_array(vars.paths);
	vars.paths = init_paths(vars.env);
	forks = want_sum_furk(cmd, vars);
	waitpid_fork(forks, vars);
	ft_free_char_array(vars.paths);
}













void	executor(t_cmd *cmd, char **env, int *last_pid)
{
	t_fork	*a_fork;
	t_fork	*head_fork_list;
	int			fd;
	bool		first_cmd;
	t_mini_vars		utils;
	
	a_fork = NULL;
	first_cmd = true;
	fd = -1;
	while (cmd)
	{
		a_fork = new_fork(a_fork);
		if (first_cmd == true)
		{
			utils = init_utils(env, last_pid);
			head_fork_list = a_fork;
			first_cmd = false;			
		}
		fd = handle_fork(a_fork, cmd, &utils, fd);
		cmd = cmd->next;
	}
	waitpid_fork(head_fork_list, utils, last_pid);
}
