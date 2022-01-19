#include <minishell.h>

static char	*get_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && ft_strlen(line))
		add_history(line);
	return (line);
}

static void	process_cmd(const char *raw_line, char **env)
{
	t_token	*tokens;
	
	(void)env;
	tokens = tokenize_cmd(raw_line);
	// parse_tokens(&tokens, raw_cmd);
	// expand_(&tokens);
	// execute_cmds(AST);
	if (!ft_strncmp(raw_line, "exit", 4))
		mini_exit();
	// free tokens
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	
	(void)argc;
	(void)argv;
	init_signals();
	while (true)
	{
		line = get_line();
		if (line && ft_strlen(line))
			process_cmd(line, env);
		printf("%s\n", line);
		free(line);
	}
}
