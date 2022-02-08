/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 16:11:43 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void mini_echo_args(char **args, int flag)
{
    int i;

    i = flag;
    ft_putstr_fd(args[i], STDOUT_FILENO);
    i++;
    while (args[i])
    {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(args[i], STDOUT_FILENO);
        i++;
    }
    if (flag == 1)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return ;
}

void	mini_echo(char **args, t_utils *utils)
{
    int flag;

    flag = 0;
    if (ft_strncmp(args[1], "-n", 2) != 0)
        flag = 1;
    mini_echo_args(args, flag);
	utils->last_pid = 0;
    exit(0);
}