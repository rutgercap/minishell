#include <minishell.h>

void	sigint_handler(int signum)
{
	write(1, &"\0", 1);
	return ;
}

void	init_action(int signum, void handler(int), char *error_name)
{
	t_sigaction	new;
	sigset_t	mask;
	
	ft_bzero(&new, sizeof(t_sigaction));
	// sigfillset(&mask);
	sigemptyset(&mask);
	new.__sigaction_u.__sa_handler = handler;
	new.sa_mask = mask;
	new.sa_flags = SA_RESTART;
	if (sigaction(signum, &new, NULL))
		exit_error(errno, error_name, NULL);
}

void	init_sigactions(void)
{
	init_action(SIGINT, sigint_handler, "init_sigint");
}
