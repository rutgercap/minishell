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

static void mini_echo_args(char **arg, bool new_line, int i)
{
    while (arg[i])
    {
        ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
        	ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (new_line == true)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

static int	check_for_flag(char **arg, char c, bool *new_line)
{
	int		i;
	int		j;

	i = 1;
	while (!ft_strncmp(arg[i], "-n", 2))
	{
		j = 2;
		while (arg[i][j] == c)
			j++;
		if (arg[i][j] == '\0')
		{
        	*new_line = false;
			i++;
		}
		else
			break ;
	}
	return (i);
}

int	mini_echo(char **arg, t_mini_vars *vars)
{
	bool	new_line;
	int		i;

	new_line = true;
	i = 1;
	if (!arg[i])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(arg[1], "-n", 2))
		i = check_for_flag(arg, arg[1][1], &new_line);
    mini_echo_args(arg, new_line, i);
	vars->last_pid = 0;
    return (EXIT_SUCCESS);
}
