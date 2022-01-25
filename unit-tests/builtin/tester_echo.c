#include "builtin_tester.h"

void	tester_echo(char **env, char *test)
{
	char	**arg;

	(void)env;
	arg = ft_split(test, ' ');
	mini_echo(arg);
	return ;
}
