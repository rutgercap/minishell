/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/09 17:04:49 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	error_handling(char *cmd, t_mini_vars *utils)
{

	return ;
}

static void	execute_cmd2(t_cmd *cmd, t_mini_vars *utils)
{
	if (execve(cmd->exec->command, cmd->exec->arguments, utils->env) == 1)
	{
		perror("");
		utils->last_pid = errno;
	}
	return ;
}

void	execute_cmd(t_cmd *cmd, t_mini_vars *utils)
{
	int		i;
	char	*str;

	if (access(cmd->exec->command, X_OK) == 0)
		execute_cmd2(cmd, utils);
	i = 0;
	while ((utils->paths[i]))
	{
		str = ft_strjoin(utils->paths[i], cmd->exec->command);
		ft_check_malloc(str, "execute_child");
		if (access(str, X_OK) == 0)
		{
			if (execve(str, cmd->exec->arguments, utils->env) == -1)
			{
				perror("");
				utils->last_pid = errno;
			}
		}
		free(str);
		i++;
	}
	error_handling(cmd->exec->command, utils);
	return ;
}
