/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:55:14 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/15 11:30:51 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

void	copy_line_env(char **new_env, char **env, int new_env_i, int env_i)
{
	int	len;

	len = ft_strlen(env[env_i]);
	new_env[new_env_i] = (char *)ft_calloc((len + 1), sizeof(char));
	ft_check_malloc(new_env[new_env_i], "copy_line_env");
	ft_strcpy(new_env[new_env_i], env[env_i], len);
}

static int	check_export_error(char *arg, int i)
{
	while (arg[i] && ft_strchr("\'\"$ ,.:/[{]}+=-*^%#@!~", arg[i]))
		i++;
	if (ft_isalpha(arg[i]) || ft_isalnum(arg[i]))
		return (EXIT_SUCCESS);
	else if (arg[i] == '\0')
		return (EXIT_FAILURE);
	else
	{
		i++;
		return (check_export_error(arg, i));
	}
}

int	check_for_error(char *arg, int type)
{
	int	i;

	i = 0;
	while (arg[i] && !ft_strchr("\'\"$ ,.:/[{]}+=-*^%#@!~", arg[i]))
		i++;
	if (arg[i] == '=' && type == EXPORT)
	{
		i++;
		return (check_export_error(arg, i));
	}
	if (arg[i] == '\0')
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
