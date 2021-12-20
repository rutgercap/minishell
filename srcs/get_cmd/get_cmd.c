#include <get_cmd.h>

/*
	print cwd and ask for command
	read a line with readline function
	if non-null -> add to history
		- what if null?
	returns command as string
*/

char	*get_cmd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_error(2, "get_cmd", "Malloc failure");
	write(1, &cwd, ft_strlen(cwd));
	free(cwd);
}