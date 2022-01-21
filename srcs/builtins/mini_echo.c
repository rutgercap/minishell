#include "builtin.h"

static void mini_echo_args(char **arg, int flag)
{
    int i;

    i = flag;
    ft_putstr_fd(arg[i], STDOUT_FILENO);
    i++;
    while (arg[i])
    {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(arg[i], STDOUT_FILENO);
        i++;
    }
    if (flag == 1)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return ;
}

void	mini_echo(char **arg)
{
    int flag;

    flag = 0;
    if (ft_strncmp(arg[0], "-n", 2) != 0)
        flag = 1;
    mini_echo_args(arg, flag);
    return ;
}