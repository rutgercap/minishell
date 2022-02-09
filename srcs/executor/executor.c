/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:10 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/09 17:59:20 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	waitpid_fork(t_fork *forks, t_mini_vars *vars)
{
	int		status;
	t_fork	*next;

	while (forks)
	{
		waitpid(forks->pid, &status, 0);
		next = forks->next;
		free(forks);
		forks = next;
	}
	if (WIFEXITED(status))
		vars->last_pid = WEXITSTATUS(status);
}

static void	child_process(t_cmd *cmd, t_mini_vars *vars, int *end, int input)
{
	int	output;
	
	input = arrange_input(cmd, input);
	if (input != -1)
	{
		if (dup2(input, STDIN_FILENO) < 0)
			exit_error(errno, "child_fork", NULL);
		close(input);
	}
	if (cmd->output)
		output = arrange_output(cmd, end[WRITE]);
	if (output != -1)
	{
		if (dup2(output, STDOUT_FILENO) < 0)
			perror("");
	}
	execute_cmd(cmd, vars);
}

/*
	https://www.youtube.com/watch?v=-TcLxlkc2pA&ab_channel=Incept
*/
static t_fork	*want_sum_furk(t_cmd *cmd, t_mini_vars *vars, int end[2])
{
	t_fork	*forks;
	int		fd;

	forks = new_fork();
	while (cmd)
	{
		fd = -1;
		forks->pid = fork();
		if (forks->pid < 0)
			exit_error(errno, "want_sum_furk", NULL);
		else if (forks->pid == CHILD)
			child_process(cmd, vars, end, fd);
		else
			close(end[READ]);
		if (cmd->next)
		{
			forks->next = new_fork();
			forks = forks->next;
		}
		cmd = cmd->next;
	}
	return (forks);
}

void	executor(t_cmd *cmd, t_mini_vars *vars)
{
	t_fork	*forks;
	int		end[2];
	
	if (pipe(end) < 0)
		exit_error(errno, "want_sum_furk", NULL);
	vars->paths = init_paths(vars->env);
	forks = want_sum_furk(cmd, vars, end);
	close(end[READ]);
	close(end[WRITE]);
	waitpid_fork(forks, vars);
	ft_free_char_array(vars->paths);
}
