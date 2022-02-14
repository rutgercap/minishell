/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/14 09:49:22 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void mini_echo_args(char **arg, bool newline)
{
    int i;

    i = 1;
    if (!newline)
        i++;
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

int	mini_echo(char **arg)
{
    bool    newline;

    newline = true;
    if (!ft_strncmp(arg[1], "-n", 2))
        newline = false;
    mini_echo_args(arg, newline);
    return (EXIT_SUCCESS);
}
