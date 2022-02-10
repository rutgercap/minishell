/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/10 09:53:18 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void mini_echo_args(char **arg, int flag)
{
    int i;

    i = flag;
    i++;
    while (arg[i])
    {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(arg[i], STDOUT_FILENO);
        i++;
    }
    if (flag == 1)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return ;
}

int	mini_echo(char **arg)
{
    int flag;

    flag = 0;
    if (ft_strncmp(arg[1], "-n", 2) != 0)
        flag = 1;
    mini_echo_args(arg + 2, flag);
    return (0);
}
