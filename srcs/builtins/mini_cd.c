/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 11:26:39 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	relative_path(t_mini_vars *vars, char *arg)
{
	char	*curr_pwd;
	char	*new_pwd;

	curr_pwd = getcwd(NULL, 0);
	ft_check_malloc(curr_pwd, "relative_path");
	if (chdir(arg) == -1)
	{
		perror("");
		vars->last_pid = errno;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	ft_check_malloc(new_pwd, "relative_path");
	set_new_paths(new_pwd, curr_pwd, vars);
	free(curr_pwd);
	free(new_pwd);
	return ;
}

static void	absolute_path(char **env, t_mini_vars *vars, char *path)
{
	char	*home_path_str;

	home_path_str = cpy_env_line(env, "HOME");
	ft_check_malloc(home_path_str, "absolute_path");
	if (chdir(path) == -1)
	{
		perror("");
		vars->last_pid = errno;
		return ;
	}
	set_new_paths(path, home_path_str, vars);
	return ;
}

static void	home_path(char **env, t_mini_vars *vars)
{
	char	*home_path_str;
	char	*curr_pwd;

	home_path_str = cpy_env_line(env, "HOME");
	ft_check_malloc(home_path_str, "home_path");
	curr_pwd = cpy_env_line(env, "PWD");
	ft_check_malloc(curr_pwd, "home_path");
	if (chdir(home_path_str) == -1)
	{
		perror("");
		vars->last_pid = errno;
		return ;
	}
	set_new_paths(home_path_str, curr_pwd, vars);
	return ;
}

static void	oldpwd_path(char **env, t_mini_vars *vars)
{
	char	*old_pwd;
	char	*curr_pwd;
	
	old_pwd = cpy_env_line(env, "OLDPWD");
	ft_check_malloc(old_pwd, "oldpwd_path");
	curr_pwd = cpy_env_line(env, "PWD");
	ft_check_malloc(curr_pwd, "oldpwd_path");
	if (chdir(old_pwd) == -1)
	{
		perror("");
		vars->last_pid = errno;
		return ;
	}
	set_new_paths(old_pwd, curr_pwd, vars);
	return ;
}

int	mini_cd(char **args, t_mini_vars *vars)
{
	if (!ft_strncmp(args[1], "-", 1))
		oldpwd_path(vars->env, vars);
	else if (!args[1])
		home_path(vars->env, vars);
	else if (args[1][0] == '/')
		absolute_path(vars->env, vars, args[1]);
	else
		relative_path(vars, args[1]);
	return (1);	
}