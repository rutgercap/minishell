#include "builtin_tester.h"

static void mini_pwd(void)
{
    char    str[100];							// dit moet ik alleen nog ff uitvogelen

    getcwd(str, 100);
    ft_putendl_fd(str, STDOUT_FILENO);
    return ;
}

void	tester_pwd(char **env)
{
	(void)env;
	mini_pwd();
}
