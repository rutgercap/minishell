/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:45:09 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/08 12:19:10 by rcappend      ########   odam.nl         */
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

static void	process_cmd(char *raw_line, char **env, int *last_pid)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, env, *last_pid);
	executor(cmd, env, last_pid);
	free_cmd_list(&cmd);
	if (!ft_strncmp(raw_line, "exit", 4))
		mini_exit();
}

/*
	Check minishell.h for info on global variable.
*/
int main(int argc, char **argv, char **env)
{
	int		last_pid;
	char	*line;
	
	(void)argc;
	(void)argv;
	last_pid = 0;
	g_interactive = 1;
	init_signals();
	while (true)
	{
		line = get_line();
		process_cmd(line, env, &last_pid);	
		free(line);
	}
}
