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
		write(2, func, ft_strlen(func));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, &"\n", 1);
	exit(code);
}
