/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 08:20:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/16 09:53:39 by rcappend      ########   odam.nl         */
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

static void	redirect_input(t_red *input, int fd)
{
	while (input)
	{
		if (input->type == RED_IPUT)
			fd = open(input->file_name, O_RDONLY);
		else if (input->type == HERE_DOC)
			ft_putendl_fd("heredoc not built", 2);
		if (fd < 0)
			file_error(input->file_name);
		if (input->next && fd != 0)
			close(fd);
		input = input->next;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error(errno, "output_redirects", NULL);
	if (fd != 0)
		close(fd);
}

static void	redirect_output(t_red *output, int fd)
{
	int	flags;

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
		if (output->next && fd != 1)
			close(fd);
		output = output->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_error(errno, "output_redirects", NULL);
	if (fd != 1)
		close(fd);
}

void	child_process(t_cmd *cmd, t_mini_vars *vars, int end[2], int input_fd)
{
	close(end[READ]);
	if (cmd->input && cmd->input->type == R_PIPE)
	{
		if (dup2(input_fd, STDIN_FILENO) < 0)
			exit_error(errno, "child_process", NULL);
		cmd->input = cmd->input->next;
	}
	redirect_input(cmd->input, input_fd);
	if (cmd->next && !cmd->output)
		redirect_output(cmd->output, end[WRITE]);
	else
		close(end[WRITE]);
	execute_cmd(cmd->exec, vars);
}

void	simple_command(t_cmd *cmd, t_mini_vars *vars)
{
	redirect_input(cmd->input, STDIN_FILENO);
	redirect_output(cmd->output, STDOUT_FILENO);
	execute_cmd(cmd->exec, vars);
}

int	handle_forks(t_fork *forks, t_cmd *cmd, t_mini_vars *vars, int fd)
{
	int		end[2];

	if (pipe(end) < 0)
		exit_error(errno, "handle_forks", NULL);
	forks->pid = fork();
	if (forks->pid < 0)
		exit_error(errno, "handle_forks", NULL);
	else if (forks->pid == CHILD)
		child_process(cmd, vars, end, fd);
	else if (forks->pid > 0)
		close(end[WRITE]);
	return (end[READ]);
}
