#include <minishell.h>

static void	sigint_handler(int signum)
{
	(void)signum;

	rl_replace_line("", 0);
	ft_putchar_fd('\n', 2);
	if (g_interactive)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putchar_fd('\n', 2);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
