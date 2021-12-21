#include "utils.h"

void	exit_errno(char *func)
{
	perror(func);
	exit(errno);
}