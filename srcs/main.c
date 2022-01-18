#include <minishell.h>

static void	process_cmd(const char *raw_line, char **env)
{
	(void)env;
	// tokenize_line
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
		line = NULL;
		get_line(&line);
		if (line && ft_strlen(line))
			process_cmd(line, env);
		printf("%s\n", line);
		free(line);
	}
}
