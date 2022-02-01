#include "builtin_tester.h"

static void	mini_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

void	tester_exit(char **env)
{
	(void)env;
	mini_exit();
	return ;
}
