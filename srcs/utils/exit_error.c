#include "utils.h"

void	exit_error(int code, char *func, char *msg)
{
	if (func)
	{
		write(2, &func, ft_strlen(func));
		write(2, ": ", 2);
	}
	write(2, &msg, ft_strlen(msg));
	exit(code);
}