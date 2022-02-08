/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/07 15:40:43 by dvan-der         ###   ########.fr       */
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
	chdir(arg[0]);
	return (1);
}

static int mini_pwd(void)
{
    char    str[100];

    getcwd(str, 100);
    ft_putendl_fd(str, STDOUT_FILENO);
    return (1);
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
    return (1);
}

int	built_in(char *word, char **arg, char **env)
{
    if (ft_strncmp(word, "echo", 4) == 0)
        return (mini_echo(arg));
    else if (ft_strncmp(word, "cd", 2) == 0)
        return (mini_cd(arg));
    else if (ft_strncmp(word, "pwd", 3) == 0)
        return (mini_pwd());
    else if (ft_strncmp(word, "export", 6) == 0)
        return (mini_export(arg, &env));
    else if (ft_strncmp(word, "unset", 5) == 0)
		return (mini_unset(arg, &env));
    else if (ft_strncmp(word, "env", 3) == 0)
        return (mini_env(env));
    else if (ft_strncmp(word, "exit", 4) == 0)
		mini_exit();
	return (0);
}
