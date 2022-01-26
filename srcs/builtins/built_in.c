#include "builtin.h"

static void	mini_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

static void	mini_cd(char **arg)
{
	chdir(arg[0]);
	return ;
}

static void mini_pwd(void)
{
    char    str[100];

    getcwd(str, 100);
    ft_putendl_fd(str, STDOUT_FILENO);
    return ;
}

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

void	built_in(char *word, char **arg, char **env)
{
    if (ft_strncmp(word, "echo", 4) == 0)
        mini_echo(arg);
    else if (ft_strncmp(word, "cd", 2) == 0)
        mini_cd(arg);
    else if (ft_strncmp(word, "pwd", 3) == 0)
        mini_pwd();
    else if (ft_strncmp(word, "export", 6) == 0)
        mini_export();
    else if (ft_strncmp(word, "unset", 5) == 0)
		mini_unset(arg, &env);
    else if (ft_strncmp(word, "env", 3) == 0)
        mini_env(env);
    else if (ft_strncmp(word, "exit", 4) == 0)
		mini_exit();
}
