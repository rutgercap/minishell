/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/10 09:07:01 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	mini_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

static int	mini_cd(char **arg)
{
	return chdir(arg[0]);
}

static int mini_pwd(void)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    ft_putendl_fd(pwd, STDOUT_FILENO);
    free(pwd);
    return (0);
}

static int	mini_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

int	built_in(char *cmd, char **args, char **env)
{
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return (mini_echo(args));
    else if (ft_strncmp(cmd, "cd", 2) == 0)
        return (mini_cd(args));
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (mini_pwd());
    else if (ft_strncmp(cmd, "export", 6) == 0)
        return (mini_export(args, &env));
    else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (mini_unset(args, &env));
    else if (ft_strncmp(cmd, "env", 3) == 0)
        return (mini_env(env));
    else if (ft_strncmp(cmd, "exit", 4) == 0)
		mini_exit();
	return (0);
}
