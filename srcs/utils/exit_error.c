#include "utils.h"

/*
	Arguments:
	code:	
		error code to exit with
	func (nullable):	
		function where the error was encountered
	msg (nullable):	
		what went wrong

	example:
	exit_error(3, "main", "malloc failure");
	should output to standard error:
	"main: malloc failure"
*/

void	exit_error(int code, char *func, char *msg)
{
	if (func)
	{
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, &"\n", 1);
	exit(code);
}
