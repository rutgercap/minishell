/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:26:10 by rcappend          #+#    #+#             */
/*   Updated: 2022/02/15 15:22:48 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

char	**init_paths(char **env)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = ft_split(env[i] + 5, ':');
	ft_check_malloc(*path, "make_path_env");
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		ft_check_malloc(temp, "init_path");
		free(path[i]);
		path[i] = temp;
		i++;
	}
	return (path);
}

t_fork	*new_fork(void)
{
	t_fork	*new_fork;
	
	new_fork = ft_calloc(1, sizeof(t_fork));
	ft_check_malloc(new_fork, "new_fork");
	return (new_fork);
}

static void	waitpid_fork(t_fork *forks, t_mini_vars *vars)
{
	int		status;
	t_fork	*next;

	while (forks)
	{
		waitpid(forks->pid, &status, 0);
		next = forks->next;
		free(forks);
		forks = next;
	}
	if (WIFEXITED(status))
		vars->last_pid = WEXITSTATUS(status);
}

void	make_forks(t_fork **head, t_cmd *cmd, t_mini_vars *vars)
{
	t_fork	*forks;
	int		fd;

	fd = 0;
	forks = new_fork();
	*head = forks;
	while (cmd)
	{
		fd = handle_forks(forks, cmd, vars, fd);
		cmd = cmd->next;
	}
}

void	executor(t_cmd *cmd, t_mini_vars *vars)
{
	t_fork	*forks;

	vars->paths = init_paths(vars->env);
	if (!built_in(cmd->exec->command, cmd->exec->arguments, vars))
	{
		make_forks(&forks, cmd, vars);
		waitpid_fork(forks, vars);
	}
	ft_free_char_array(vars->paths);
}
