/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 11:30:12 by dvan-der         ###   ########.fr       */
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
		*last_pid = WEXITSTATUS(status);
	return ;
}

static void	child_fork(t_cmd *cmd, t_utils *utils, int *end, int fd)
{
	int	input;
	int	output;
	
	close(end[0]);
	input = arrange_input(cmd, fd, &utils->last_pid);
	if (input != -1)
	{
		if (dup2(input, STDIN_FILENO) < 0)
			perror("");
		// ft_putstr_fd("input duplicated: ", 2);
		// ft_putnbr_fd(input, 2);
		// ft_putchar_fd('\n', 2);
		close(input);
	}
	output = arrange_output(cmd, end[1], &utils->last_pid);
	// ft_putchar_fd('\n', 2);
	// ft_putnbr_fd(output, 2);
	// ft_putchar_fd('\n', 2);
	if (output != -1)
	{
		if (dup2(output, STDOUT_FILENO) < 0)
			perror("");
		// ft_putstr_fd("output duplicated: ", 2);
		// ft_putnbr_fd(output, 2);
		// ft_putchar_fd('\n', 2);
		// close(output);
	}
	close(end[1]);
	// ft_putendl_fd("Lets go executor", 2);
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

static t_fork_list	*new_fork(t_fork_list *a_fork)
{
	t_fork_list	*new_fork;
	
	new_fork = (t_fork_list *)malloc(sizeof(t_fork_list));
	ft_check_malloc(new_fork, "new_fork");
	new_fork->next = NULL;
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
	fd = -1;
	while (cmd)
	{
		a_fork = new_fork(a_fork);
		// ft_putstr_fd("fd before handle_fork: ", 2);
		// ft_putnbr_fd(fd, 2);
		// ft_putchar_fd('\n', 2);
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
