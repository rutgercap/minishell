/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 11:34:10 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static void mini_echo_args(char **arg, bool newline)
{
    int i;

    i = 1;
    if (!newline)
        i++;
    while (arg[i])
    {
        ft_putstr_fd(arg[i], STDOUT_FILENO);
        ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

int	mini_echo(char **arg, t_mini_vars *vars)
{
    bool    newline;

    newline = true;
	if (!arg[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
    if (!ft_strncmp(arg[1], "-n", 2))
	{
		if (arg[1][2] == '\0')
        	newline = false;
	}
    mini_echo_args(arg, newline);
	vars->last_pid = 0;
    return (EXIT_SUCCESS);
}
