/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/09 17:39:23 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**init_paths(char **env)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = ft_split(env[i] + 5, ':');
	ft_check_malloc(*path, "make_path_env");
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		ft_check_malloc(temp, "init_path");
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}

t_fork	*new_fork(void)
{
	t_fork	*new_fork;
	
	new_fork = ft_calloc(1, sizeof(t_fork));
	ft_check_malloc(new_fork, "new_fork");
	return (new_fork);
}

int	arrange_input(t_red *input, int pipe_fd)
{
	int	input;

	input = pipe_fd;
	while (input)
	{
		if (input != -1)
			close(input);
		if (input->type == RED_IPUT)
			input = open(input->file_name, O_RDONLY);
		else
			ft_putstr_fd("heredoc not fixed", STDERR_FILENO);
		if (input < 0)
			exit_error(errno, "arrange_input", NULL);
		if (input->next)
			close(input);
		input = input->next;
	}
	return (input);
}

int	arrange_output(t_red *output, int pipe_fd)
{
	int	output;
	int	flags;

	output = pipe_fd;
	while (output)
	{
		flags = O_CREAT | O_RDWR;
		if (output->type == RED_OPUT_A)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		output = open(output->file_name, flags, 0644);
		if (output < 0)
			exit_error(errno, "arrange_output", NULL);
		if (output->next)
			close(output);
		output = output->next;
	}
	return (output);	
}
