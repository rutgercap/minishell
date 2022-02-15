/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 08:20:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/14 16:24:29 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static void	file_error(const char *filename)
{
	perror("minishell");
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(filename, 2);
	exit (errno);
}

static void	redirect_input(t_red *input)
{
	int	fd;
	
	while (input)
	{
		if (input->type == RED_IPUT)
			fd = open(input->file_name, O_RDONLY);
		else
			ft_putendl_fd("heredoc not built", 2);
		if (fd < 0)
			file_error(input->file_name);
		input = input->next;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error(errno, "output_redirects", NULL);
}

static void	redirect_output(t_red *output)
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
}

void	child_process(t_cmd *cmd, t_mini_vars *vars, int end[2], int input_fd)
{
	if (cmd->input && cmd->input->type == R_PIPE)
	{
		if (dup2(input_fd, STDIN_FILENO) < 0)
			exit_error(errno, "child_process", NULL);
		cmd->input = cmd->input->next;
	}
	if (cmd->next && !cmd->output)
	{
		if (dup2(end[WRITE], STDOUT_FILENO) < 0)
			exit_error(errno, "child_process", NULL);
	}
	else
		close(end[WRITE]);
	redirect_input(cmd->input);
	redirect_output(cmd->output);
	execute_cmd(cmd->exec, vars);
}
