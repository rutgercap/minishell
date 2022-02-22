/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 11:13:27 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/21 16:04:45 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

/*
	Bash overflowt met exit codes vanaf 255
	if no arguments > exit with last pid
*/
void	error(char *args, t_mini_vars *vars)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(args, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	vars->last_pid = 255;
}

int		process_args(char **args, t_mini_vars *vars)
{
	bool	nondigit_argument;
	int		i;
	
	i = 0;
	nondigit_argument = false;
	while (args[i])
	{
		if (ft_strcheck(args[i], ft_isdigit))
			return (true);
		else if (!nondigit_argument)
		{
			error(args[i], vars);
			nondigit_argument = true;
		}
		i++;
	}
	return (false);
}

int	mini_exit(char **args, t_mini_vars *vars)
{
	bool	should_exit;
	
	ft_putendl_fd("exit", STDERR_FILENO);
	should_exit = true;
	if (args[1])
		should_exit = process_args(args + 1, vars);
	if (should_exit)
    	exit((unsigned char)vars->last_pid);
	return (vars->last_pid);
}
