#include <minishell.h>

static char	**init_env(char **env)
{
	char	**new_env;
	int		i;
	int		len;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc((i + 1) * sizeof(char *));
	ft_check_malloc(new_env, "init_env");
	i = 0;
	while (env[i])
	{
		len = strlen(env[i]);
		new_env[i] = (char *)ft_calloc(len + 1, sizeof(char));
		ft_check_malloc(new_env[i], "init_env");
		ft_strlcpy(new_env[i], env[i], len + 1);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static char	*get_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && ft_strlen(line))
		add_history(line);
	return (line);
}

static void	process_cmd(char *raw_line, char **env, int *last_pid)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, env, *last_pid);
	env = executor(cmd, env, last_pid);
	free_cmd_list(&cmd);
	if (!ft_strncmp(raw_line, "exit", 4))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		mini_exit();
	}
}

int main(int argc, char **argv, char **env)
{
	int		last_pid;
	char	*line;
	char	**new_env;
	
	(void)argc;
	(void)argv;
	last_pid = 0;
	new_env = init_env(env);
	// while (new_env[last_pid])
	// {
	// 	printf("%s\n", new_env[last_pid]);
	// 	last_pid++;
	// }
	init_signals();
	while (true)
	{
		line = get_line();
		if (line && ft_strlen(line))
			process_cmd(line, new_env, &last_pid);
		free(line);
	}
}
