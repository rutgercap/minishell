#include <minishell.h>

int	get_cmd(char **dest)
{
	char	*line;
	size_t	len;

	write(STDOUT_FILENO, &"\nminishell$ ", 13);
	if (getline(&line, &len, stdin) == -1)
		exit_error(errno, "Prompt user", NULL);
	if (ft_strlen(line) != 0)
	{
		// add_history(dest);
		*dest = line;
		return (EXIT_SUCCESS);
	}
	free(line);
	return (EXIT_FAILURE);
}

int main(void)
{
	char	*cmd;
	
	// print minishell info?
	init_sigactions();
	cmd = NULL;
	while (true)
	{
		get_cmd(&cmd);
		// lex command
		printf("%s", cmd);
		free(cmd);
		// parse command
		// expand command
		// execute command
	}
}
