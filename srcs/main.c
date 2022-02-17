/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:45:09 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/17 13:08:39 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**init_env(char **env)
{
	char	**mini_env;
	int		len;

	len = 0;
	while (env[len])
		len++;
	mini_env = ft_calloc(len + 1, sizeof(char *));
	ft_check_malloc(mini_env, "init_env");
	while (len)
	{
		len--;
		mini_env[len] = ft_strdup(env[len]);
		ft_check_malloc(mini_env[len], "init_env");
	}
	return (mini_env);
}

static void	process_cmd(char *raw_line, t_mini_vars *vars)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, vars->env, vars->last_pid);
	if (!cmd)
		return ;
	signal(SIGQUIT, sigquit_handler);
	g_interactive = 0;
	executor(cmd, vars);
	free_cmd_list(&cmd);
}

static char	*get_line(void)
{
	char	*line;

	while (true)
	{
		init_signals();
		line = readline("minishell$ ");
		if (!line)
			exit(EXIT_SUCCESS);
		else if (ft_strlen(line))
		{
			add_history(line);
			return (line);
		}
		free(line);
	}
}

int main(int argc, char **argv, char **env)
{
	t_mini_vars	vars;
	char		*line;
	
	// (void)argc;
	// (void)argv;
	vars = init_minishell(env);
	g_interactive = 1;
	if (argc == 2)
	{
		process_cmd(argv[1], &vars);
		return (vars.last_pid);
	}
	while (true)
	{
		g_interactive = INTERACT;
		line = get_line();
		process_cmd(line, &vars);	
		free(line);
	}
}
