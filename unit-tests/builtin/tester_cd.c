#include "builtin_tester.h"

static void	mini_cd(char **arg)
{
	chdir(arg[0]);
	return ;
}

void tester_cd(char **env, char **arg)
{
	(void)env;
	mini_cd(arg);
	return ;
}