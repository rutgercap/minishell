/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/09 13:56:10 by rcappend      ########   odam.nl         */
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
	path = ft_split(env[i], ':');
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

t_mini_vars	init_utils(char **env, int *last_pid)
{
	int		i;
	char	**path_env;
	t_mini_vars	utils;

	i = 0;
	while ((env)[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	path_env = init_paths(env[i]);
	ft_check_malloc(path_env, "make_path");
	utils.paths = path_env;
	utils.last_pid = *last_pid;
	utils.env = env;
	return (utils);
}

static t_fork	*new_fork(t_fork *a_fork)
{
	t_fork	*new_fork;
	
	new_fork = ft_calloc(1, sizeof(t_fork));
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

int	arrange_output(t_cmd *cmd, int write_pipe_end, int *last_pid)
{
	int	output;
	int	flags;

	if (cmd->next)
		output = write_pipe_end;
	else
		output = 1;
	while(cmd->output)
	{
		flags = O_CREAT | O_RDWR;
		if (cmd->output->type == RED_OPUT_A)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		output = open(cmd->output->file_name, flags, 0644);
		if (output < 0 || output > 1024)
		{
			ft_putstr_fd(cmd->output->file_name, 2);
			perror("");
			*last_pid = errno;
			return (-1);
		}
		if (cmd->output->next)
			close(output);
		cmd->output = cmd->output->next;
	}
	return (output);	
}

int	arrange_input(t_cmd *cmd, int fd, int *last_pid)
{
	int	input;

	input = fd;
	while(cmd->input)
	{
		if (input != -1)
			close(input);
		input = open(cmd->input->file_name, O_RDONLY);
		if (input < 0 || input > 1024)
		{
			ft_putstr_fd(cmd->input->file_name, 2);
			perror("");
			*last_pid = errno;
			return (-1);
		}
		if (cmd->input->next)
			close(input);
		cmd->input = cmd->input->next;
	}
	return (input);
}
