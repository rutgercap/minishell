/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 14:23:15 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	copy_line_env(char **new_env, char **env, int new_env_i, int env_i)
{
	int	len;

	len = ft_strlen(env[env_i]);
	new_env[new_env_i] = (char *)ft_calloc((len + 1), sizeof(char));
	ft_check_malloc(new_env[new_env_i], "copy_line_env");
	ft_strcpy(new_env[new_env_i], env[env_i], len);
}

static char **edit_env_export(char **env, char *arg, int edit_row, int size_old_env)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((size_old_env + 1) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_export");
	i = 0;
	while (env[i])
	{
		if (i == edit_row)
			copy_line_env(new_env, &arg, i, 0);
		else
			copy_line_env(new_env, env, i, i);
		i++;
	}
	new_env[i] = NULL;
	free_old_env(env);
	return (new_env);
}

static int	find_var(char *arg, char **env)
{
	int		i;
	int		len;

	len = 0;
	while (arg[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0)
		{
			if (env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

int	mini_export(char **arg, char ***env)
{
	int		i;
	int		edit_row;
	int		size_old_env;

	size_old_env = 0;
	while ((*env)[size_old_env])
		size_old_env++;
	i = 0;
	while (arg[i])
	{
		edit_row = find_var(arg[i], *env);
		if (edit_row == -1)
		{
			i++;
			continue ;
		}
		*env = edit_env_export(*env, arg[i], edit_row, size_old_env);
		i++;
	}
	return (1);
}
