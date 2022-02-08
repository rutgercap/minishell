/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 16:29:56 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	mini_exit(void)
{
	exit(0);
}

static void	mini_cd(char **args, t_utils *utils)
{
	if (chdir(args[1]) == -1)
		perror("");
	utils->last_pid = errno;
	exit(errno);
}

static void mini_pwd(t_utils *utils)
{
    char    *str;

    str = getcwd(NULL, 0);
	if (!str)
	{
		perror("");
		utils->last_pid = errno;
		exit(errno);
	}
	else
    	ft_putendl_fd(str, STDOUT_FILENO);
	utils->last_pid = 0;
	exit(0);
}

static void	mini_env(char **env, t_utils *utils)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
	utils->last_pid = 0;
	exit(0);
}

void	built_in(t_cmd *cmd, t_utils *utils)
{
    if (ft_strncmp(cmd->exec->cmd, "echo", 4) == 0)
        mini_echo(cmd->exec->args, utils);
    else if (ft_strncmp(cmd->exec->cmd, "cd", 2) == 0)
        mini_cd(cmd->exec->args, utils);
    else if (ft_strncmp(cmd->exec->cmd, "pwd", 3) == 0)
        mini_pwd(utils);
    else if (ft_strncmp(cmd->exec->cmd, "export", 6) == 0)
        mini_export(cmd->exec->args, &utils->env, utils);
    else if (ft_strncmp(cmd->exec->cmd, "unset", 5) == 0)
		mini_unset(cmd->exec->args, &utils->env, utils);
    else if (ft_strncmp(cmd->exec->cmd, "env", 3) == 0) // what if args?
        mini_env(utils->env, utils);
    else if (ft_strncmp(cmd->exec->cmd, "exit", 4) == 0)
		mini_exit();
	return ;
}
