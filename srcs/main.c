/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:45:09 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/10 09:55:58 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_line(void)
{
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		if (line && ft_strlen(line))
		{
			if (*line == CTRL_D)
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				exit(0);
			}
			add_history(line);
			return (line);
		}
		free(line);
	}
}

static void	process_cmd(char *raw_line, t_mini_vars *vars)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, vars->env, vars->last_pid);
	if (!cmd)
		return ;
	executor(cmd, vars);
	free_cmd_list(&cmd);
	if (!ft_strncmp(raw_line, "exit", 4))
		mini_exit();
}

int main(int argc, char **argv, char **env)
{
	t_mini_vars	vars;
	char		*line;
	
	(void)argc;
	(void)argv;
	vars = init_minishell(env);
	g_interactive = 1;
	while (true)
	{
		line = get_line();
		process_cmd(line, &vars);	
		free(line);
	}
}
