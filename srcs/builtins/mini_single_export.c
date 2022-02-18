/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 15:05:58 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	printwithsecondquote(char *line)
{
	while (*line && *line != '=')
		line++;
	line++;
	while (*line)
	{
		ft_putchar_fd(*line, STDOUT_FILENO);
		line++;
	}
	ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	printwithfirstquote(char *line)
{
	while (*line && *line != '=')
	{
		ft_putchar_fd(*line, STDOUT_FILENO);
		line++;
	}
	ft_putchar_fd(*line, STDOUT_FILENO);
	ft_putchar_fd('\"', STDOUT_FILENO);
}

void	mini_single_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printwithfirstquote(env[i]);
		printwithsecondquote(env[i]);
		i++;
	}
	return ;
}
