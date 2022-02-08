#include <minishell.h>

void	sigint_handler(int signum)
{
	(void)signum;
	if (g_interactive)
		rl_replace_line("Minishell$ ", 0);
	else
		exit(130);
}

void	sigquit_handler(int signum)
{
	(void)signum;
	if (g_interactive)
		return ;
	else
		exit(131);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler); // broken again ???
}
