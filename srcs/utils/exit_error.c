#include "utils.h"

/*
	Exit function to use when something goes wrong.
	Can either be used with a custom error message or errno. 
	When used with errno, perror is used for error message.

	Arguments:
	code:	
		error code to exit with
	func (nullable):	
		function where the error was encountered
	msg (nullable):	
		custom error message

	example:
	exit_error(3, "main", "malloc failure");
	should output to standard error:
	"main: malloc failure"
	or
	exit_error(errno, "main", NULL);
	should output to standard error:
	main: <errno message>
	both functions exit with given exit code after displaying error message
*/

void	write_custom_msg(const char *func, const char *msg)
{
	if (func)
	{
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, &"\n", 1);
}

void	exit_error(const int code, const char *func, const char *msg)
{
	if (code == errno)
		perror(func);
	else if (func || msg)
		write_custom_msg(func, msg);
	exit(code);
}
