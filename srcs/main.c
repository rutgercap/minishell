#include <minishell.h>

static char	*get_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && ft_strlen(line))
		add_history(line);
	return (line);
}

static void	process_cmd(char *raw_line, char **env)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens);
	free_tokens(&tokens);
	// execute_cmds(AST);
	if (!ft_strncmp(raw_line, "exit", 4))
		mini_exit();
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
