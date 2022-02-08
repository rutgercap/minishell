/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 10:39:27 by dvan-der         ###   ########.fr       */
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
		utils->last_pid = errno; // 2
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		utils->last_pid = errno; // 127
	}
	return ;
}

static void	execute_cmd2(t_cmd *cmd, t_utils *utils)
{
	if (execve(cmd->exec->command, cmd->exec->arguments, utils->env) == 1)
	{
		perror("");
		utils->last_pid = errno;
	}
	return ;
}

void	execute_cmd(t_cmd *cmd, t_utils *utils)
{
	int		i;
	char	*str;

	// ft_putendl_fd("ik ben in execute_cmd", 2);
	if (access(cmd->exec->command, F_OK && X_OK) == 0)
		execute_cmd2(cmd, utils);
	i = 0;
	while ((utils->path_env[i]))
	{
		str = ft_strjoin(utils->path_env[i], cmd->exec->command);
		ft_check_malloc(str, "execute_child");
		if (access(str, F_OK && X_OK) == 0)
		{
			if (execve(str, cmd->exec->arguments, utils->env) == -1)
			{
				perror("");
				utils->last_pid = errno;
			}
			// ft_putstr_fd("execve executed", 2);
			// ft_putchar_fd('\n', 2);
		}
		free(str);
		i++;
	}
	error_handling(cmd->exec->command, utils);
	return ;
}
