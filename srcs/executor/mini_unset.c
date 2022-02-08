/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/08 16:26:01 by dvan-der         ###   ########.fr       */
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

static char	**edit_env_unset(char **env, int exl_row, int size_old_env)
{
	char	**new_env;
	int		env_i;
	int		new_env_i;

	new_env = (char **)malloc((size_old_env) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_unset");
	env_i = 0;
	new_env_i = 0;
	while (env_i < size_old_env)
	{
		if (env_i == exl_row)
		{
			env_i++;
			continue ;
		}
		copy_line_env(new_env, env, new_env_i, env_i);
		env_i++;
		new_env_i++;
	}
	new_env[new_env_i] = NULL;
	free_old_env(env);
	return (new_env);
}

static int	check_in_env_unset(char *args, char **env)
{
	int	i;
	int	len;

	len = ft_strlen(args);
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

void	mini_unset(char **args, char ***env, t_utils *utils)
{
	int	i;
	int	exl_row;
	int	size_old_env;

	i = 0;
	while (args[i])
	{
		exl_row = check_in_env_unset(args[i], *env);
		if (exl_row == -1)
		{
			i++;
			continue ;
		}
		size_old_env = 0;
		while ((*env)[size_old_env])
			size_old_env++;
		*env = edit_env_unset(*env, exl_row, size_old_env);
		i++;
	}
	utils->last_pid = 0;
	exit(0);
}