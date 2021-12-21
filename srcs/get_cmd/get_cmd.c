#include <get_cmd.h>

/*
	print program name
	read a line with readline function
	if non-null -> add to history
		- what if null?
	returns command as string
*/

char	*prompt_user(void)
{
	char	*line;
	size_t	len;
	
	line = NULL;
	write(STDOUT_FILENO, &"minishell$ ", 12);
	if (getline(&line, &len, stdin) == ERROR) {
		exit_errno("Prompt user");
	}
	return (line);
}

int	get_cmd(char **dest)
{
	char	*line;
	
	line = prompt_user();
	// add to history
	*dest = line;
	return (EXIT_SUCCESS);
}
