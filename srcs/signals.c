#include <minishell.h>

void	sigint_handler(int signum)
{
	(void)signum;	// stops compiler errors
	rl_replace_line("", 0);
}

void	sigquit_handler(int signum)
{
	(void)signum; // stops compiler errors
	printf("ctrld\n");
	mini_exit();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler); // broken again ???
}
