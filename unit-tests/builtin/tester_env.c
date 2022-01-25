#include "builtin_tester.h"

static void	mini_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return ;
}

void	tester_env(char **env)
{
	mini_env(env);
	return ;
}
