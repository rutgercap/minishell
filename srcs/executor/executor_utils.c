/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/08 09:26:47 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**make_path_env(char *str)
{
	char	**arr;
	char	*new_str;
	int		len;
	int		i;

	len = ft_strlen(str);
	new_str = ft_substr(str, 5, len - 5);
	ft_check_malloc(new_str, "make_path_env");
	arr = ft_split(new_str, ':');
	free(new_str);
	ft_check_malloc(*(arr), "make_path_env");
	i = 0;
	while (arr[i])
	{
		new_str = ft_strjoin(arr[i], "/");
		free(arr[i]);
		arr[i] = new_str;
		ft_check_malloc(arr[i], "make_path_env");
		i++;
	}
	return (arr);
}

t_utils	init_utils(char **env, int *last_pid)
{
	int		i;
	char	**path_env;
	t_utils	utils;

	i = 0;
	while ((env)[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	path_env = make_path_env(env[i]);
	ft_check_malloc(path_env, "make_path");
	utils.path_env = path_env;
	utils.last_pid = *last_pid;
	utils.env = env;
	return (utils);
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
		input = open(cmd->input->file_name, O_RDONLY);
		if (input < 0 || input > 1024)
		{
			ft_putstr_fd(cmd->input->file_name, 2);
			perror("");
			*last_pid = errno;
			return (-1);
		}
		cmd->input = cmd->input->next;
	}
	return (input);
}
