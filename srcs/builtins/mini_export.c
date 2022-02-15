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

static void	copy_line_env(char **new_env, char **env, int new_env_i, int env_i)
{
	int	len;

	len = ft_strlen(env[env_i]);
	new_env[new_env_i] = (char *)ft_calloc((len + 1), sizeof(char));
	ft_check_malloc(new_env[new_env_i], "copy_line_env");
	ft_strcpy(new_env[new_env_i], env[env_i], len);
}

static char **edit_env_export(char **env, char *args, int edit_row_nr, int size_old_env)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((size_old_env + 1) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_export");
	i = 0;
	while (env[i])
	{
		if (i == edit_row_nr)
			copy_line_env(new_env, &args, i, 0);
		else
			copy_line_env(new_env, env, i, i);
		i++;
	}
	new_env[i] = NULL;
	ft_free_char_array(env);
	return (new_env);
}

int	search_in_env(char *args, char **env)
{
	int		i;
	int		len;

	len = 0;
	while (args[len] != '=' && args[len])
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], args, len) == 0)
		{
			if (env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**ft_export(char *arg, char **env, t_mini_vars *vars)
{
	int		edit_row_nr;
	int		size_old_env;
	char	**new_env;

	edit_row_nr = search_in_env(arg, env);
	if (edit_row_nr == -1)
		return (env);
	size_old_env = 0;
	while (env[size_old_env])
		size_old_env++;
	new_env = edit_env_export(env, arg, edit_row_nr, size_old_env);
	ft_check_malloc(new_env, "ft_export");
	vars->last_pid = 0;
	return (new_env);
}

int	mini_export(char **args, t_mini_vars *vars)
{
	int	i;
	
	i = 1;
	while (args[i])
	{
		vars->env = ft_export(args[i], vars->env, vars);
		i++;
	}
	return (1);
}
