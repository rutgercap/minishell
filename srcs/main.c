#include <minishell.h>

static int	get_cmd(char **dest)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && ft_strlen(line) != 0)
	{
		add_history(line);
		*dest = line;
		return (EXIT_SUCCESS);
	}
	free(line);
	return (EXIT_FAILURE);
}

static void	process_cmd(const char *raw_cmd)
{
	// char	**tokens;
	
	// parse_cmd(&tokens, raw_cmd);
	// expand_cmd(&tokens);
	// execute_cmds(tokens);
	if (!ft_strncmp(raw_cmd, "exit", 4))
		mini_exit();
}

int main(void)
{
	char	*cmd;
	
	init_signals();
	while (true)
	{
		cmd = NULL;
		get_cmd(&cmd);
		if (cmd && ft_strlen(cmd) != 0)
			process_cmd(cmd);
		free(cmd);
	}
}
