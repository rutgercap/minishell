/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 15:10:19 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

int	mini_exit(void)
{
	exit(0);
}

static int mini_pwd(t_mini_vars *vars)
{
    char    *str;

    str = getcwd(NULL, 0);
	if (!str)
	{
		perror("");
		vars->last_pid = errno;
		exit(errno);
	}
	else
    	ft_putendl_fd(str, STDOUT_FILENO);
	free(str);
	vars->last_pid = 0;
	return (1);
}

static int	mini_env(char **env, t_mini_vars *vars)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
	vars->last_pid = 0;;
    return (1);
}

int	built_in(char *cmd, char **args, t_mini_vars *vars)
{
    if (!ft_strncmp(cmd, "echo", 4)  && cmd[4] == '\0')
        return (mini_echo(args, vars));
    else if (!ft_strncmp(cmd, "cd", 2)  && cmd[2] == '\0')
        return (mini_cd(args, vars));
    else if (!ft_strncmp(cmd, "pwd", 3)  && cmd[3] == '\0')
        return (mini_pwd(vars));
    else if (!ft_strncmp(cmd, "export", 6)  && cmd[6] == '\0')
        return (mini_export(args, vars));
    else if (!ft_strncmp(cmd, "unset", 5)  && cmd[5] == '\0')
		return (mini_unset(args, vars));
    else if (!ft_strncmp(cmd, "env", 3)  && cmd[3] == '\0')
        return (mini_env(vars->env, vars));
    else if (!ft_strncmp(cmd, "exit", 4)  && cmd[4] == '\0')
		mini_exit();
	return (0);
}
