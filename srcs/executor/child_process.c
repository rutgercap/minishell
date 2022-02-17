/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:20:35 by rcappend          #+#    #+#             */
/*   Updated: 2022/02/17 10:37:58 by dvan-der         ###   ########.fr       */
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

void	redirect_input(t_red *input, int fd)
{
	while (input)
	{
		if (fd != 0)
			close(fd);
		if (input->type == RED_IPUT)
			fd = open(input->file_name, O_RDONLY);
		else if (input->type == HERE_DOC)
			fd = here_doc(input->file_name);
		if (fd < 0)
			file_error(input->file_name);
		input = input->next;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_error(errno, "redirect_input", NULL);
	if (fd != 0)
		close(fd);
}

void	redirect_output(t_red *output, int fd)
{
	int	flags;

	while (output)
	{
		if (fd != 1)
			close(fd);
		flags = O_CREAT | O_RDWR;
		if (output->type == RED_OPUT_A)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		fd = open(output->file_name, flags, 0644);
		if (fd < 0)
			file_error(output->file_name);
		output = output->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_error(errno, "redirect_output", NULL);
	if (fd != 1)
		close(fd);
}

void	child_process(t_cmd *cmd, t_mini_vars *vars, int end[2], int input_fd)
{
	close(end[READ]);
	redirect_input(cmd->input, input_fd);
	if (cmd->next)
		redirect_output(cmd->output, end[WRITE]);
	else
		redirect_output(cmd->output, 1);
	execute_cmd(cmd, cmd->exec, vars);
}

int	handle_forks(t_fork *forks, t_cmd *cmd, t_mini_vars *vars, int fd)
{
	int		end[2];

	if (pipe(end) < 0)
		exit_error(errno, "want_sum_furk", NULL);
	forks->pid = fork();
	if (forks->pid < 0)
		exit_error(errno, "want_sum_furk2", NULL);
	else if (forks->pid == CHILD)
		child_process(cmd, vars, end, fd);
	else if (forks->pid > 0)
		close(end[WRITE]);
	return (end[READ]);
}
