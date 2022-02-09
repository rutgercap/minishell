/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/09 08:36:34 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	error_handling(char *cmd, t_utils *utils)
{
	if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		utils->last_pid = errno;
		exit(errno);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": cmd not found\n", 2);
		utils->last_pid = errno;
		exit(errno);
	}
	return ;
}

static void	execute_with_path(t_cmd *cmd, t_utils *utils)
{
	if (access(cmd->exec->cmd, F_OK && X_OK) == 0)
	{
		if (execve(cmd->exec->cmd, cmd->exec->args, utils->env) == 1)
		{
			perror("");
			utils->last_pid = errno;
		}
	}
	return ;
}

void	execute_cmd(t_cmd *cmd, t_utils *utils)
{
	int		i;
	char	*str;

	execute_with_path(cmd, utils);
	i = 0;
	while (utils->path_env[i])
	{
		str = ft_strjoin(utils->path_env[i], cmd->exec->cmd);
		ft_check_malloc(str, "execute_child");
		if (access(str, F_OK && X_OK) == 0)
		{
			if (execve(str, cmd->exec->args, utils->env) == -1)
			{
				perror("");
				utils->last_pid = errno;
			}
		}
		free(str);
		i++;
	}
	error_handling(cmd->exec->cmd, utils);
	return ;
}
