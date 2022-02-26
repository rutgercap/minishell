/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 08:20:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/25 13:00:09 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

int	file_error(const char *filename)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (filename)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
	return (1);
}

static int	duplicate(int fd, int in_out_fileno, t_mini_vars *vars)
{
	int	exit_status;

	if (dup2(fd, in_out_fileno) < 0)
	{
		perror("");
		ft_putchar_fd('\n', 2);
		vars->last_pid = errno;
		exit_status = EXIT_FAILURE;
	}
	exit_status = EXIT_SUCCESS;
	if (fd != 0 && fd != 1)
		close(fd);
	return (exit_status);
}

int	redirect_input(t_red *input, int fd, t_mini_vars *vars)
{
	char	*file_name_error;

	file_name_error = NULL;
	while (input)
	{
		if (fd != 0)
			close(fd);
		if (input->type == RED_IPUT)
			fd = open(input->file_name, O_RDONLY);
		else if (input->type == HERE_DOC)
			fd = here_doc(input->file_name);
		if (fd < 0 && !file_name_error)
			file_name_error = input->file_name;
		input = input->next;
	}
	if (!file_name_error)
		return (duplicate(fd, STDIN_FILENO, vars));
	else
		return (file_error(file_name_error));
}

int	redirect_output(t_red *output, int fd, t_mini_vars *vars)
{
	int		flags;
	char	*file_name_error;

	file_name_error = NULL;
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
		if (fd < 0 && !file_name_error)
			file_name_error = output->file_name;
		output = output->next;
	}
	if (!file_name_error)
		return (duplicate(fd, STDOUT_FILENO, vars));
	else
		return (file_error(file_name_error));
}
