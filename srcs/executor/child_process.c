/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 08:20:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/10 09:52:20 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static void	input_redirects(t_red *input)
{
	int	fd;

	while (input)
	{
		if (input->type == RED_IPUT)
			fd = open(input->file_name, O_RDONLY);
		else
			ft_putstr_fd("heredoc not implemented", STDERR_FILENO);
		if (fd < 0)
			exit_error(errno, "minishell", NULL);
		input = input->next;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error(errno, "output_redirects", NULL);
	close(fd);
}

static void	output_redirects(t_red *output)
{
	int	flags;
	int	fd;

	while (output)
	{
		flags = O_CREAT | O_RDWR;
		if (output->type == RED_OPUT_A)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		fd = open(output->file_name, flags, 0644);
		if (fd < 0)
			exit_error(errno, "output_redirects", NULL);
		output = output->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_error(errno, "output_redirects", NULL);
	close(fd);
}

void	child_process(t_cmd *cmd, t_mini_vars *vars, int end[2], int input)
{
	if (!cmd->input)
	{
		if (dup2(end[READ], STDIN_FILENO) < 0)
			exit_error(errno, "child_process", NULL);
	}
	else
		input_redirects(cmd->input);
	if (!cmd->output && cmd->next)
	{
		ft_putstr_fd("input", 1);
		if (dup2(end[WRITE], STDOUT_FILENO) < 0)
			exit_error(errno, "child_process", NULL);	
	}
	else
		output_redirects(cmd->output);
	execute_cmd(cmd->exec, vars);
}
