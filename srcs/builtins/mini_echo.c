#include <builtin.h>

static void mini_echo_args(char **arg, bool flag)
{
    int i;

    i = 0 + flag;
    ft_putstr_fd(arg[i], STDOUT_FILENO);
    i++;
    while (arg[i])
    {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(arg[i], STDOUT_FILENO);
        i++;
    }
    if (flag)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return ;
}

void	mini_echo(char **arg)
{
    bool    newline;

    if (ft_strncmp(arg[0], "-n", 2) != 0)
        newline = true;
    else
        newline = false;
    mini_echo_args(arg, newline);
    return ;
}