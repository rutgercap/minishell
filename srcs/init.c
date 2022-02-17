#include <minishell.h>

char	**init_env(char **env)
{
	char	**mini_env;
	int		len;

	len = 0;
	while (env[len])
		len++;
	mini_env = ft_calloc(len + 1, sizeof(char *));
	ft_check_malloc(mini_env, "init_env");
	while (len)
	{
		len--;
		mini_env[len] = ft_strdup(env[len]);
		ft_check_malloc(mini_env[len], "init_env");
	}
	return (mini_env);
}

void	sigint_handler_in_process(int signum)
{
	(void) signum;
	printf("\n");
}

void	sigquit_handler_in_process(int signum)
{
	(void) signum;
	printf("Quit: %d\n", signum);
}

void	sigint_handler(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_handler_endl(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	sigquit_handler(int signum)
// {
// 	(void)signum;
// 	if (g_interactive)
// 		return ;
// 	else
// 		exit(131);
// }

t_mini_vars	init_minishell(char **env)
{
	t_mini_vars	vars;
	
	vars.last_pid = 0;
	vars.env = init_env(env);
	signal(SIGINT, sigint_handler_endl);
	signal(SIGQUIT, SIG_IGN);
	return (vars);
}