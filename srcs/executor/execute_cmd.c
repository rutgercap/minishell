/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 13:55:14 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/14 15:05:08 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

char	*get_full_command(char *command, char **paths)
{
	char	*temp;
	int		i;

	if (!access(command, X_OK))
		return (command);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], command);
		ft_check_malloc(temp, "get_full_command");
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

void	execute_cmd(t_exec *exec, t_mini_vars *vars)
{
	char	*full_cmd;
	
	if (built_in(exec->command, exec->arguments, vars->env))
		return ;
	full_cmd = get_full_command(exec->command, vars->paths);
	if (!full_cmd)
		command_not_found(exec->command);
	if (execve(full_cmd, exec->arguments, vars->env) < 0)
		exit_error(errno, "execute_cmd", NULL);
}
