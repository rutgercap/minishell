#include <minishell.h>

static char	**init_env(char **env)
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

static void	sigint_handler(int signum)
{
	(void)signum;
	if (g_interactive)
		rl_replace_line("\nminishell$ ", 0);
	else
		exit(130);
}

static void	sigquit_handler(int signum)
{
	(void)signum;
	if (g_interactive)
		return ;
	else
		exit(131);
}

t_mini_vars	init_minishell(char **env)
{
	t_mini_vars	vars;
	
	vars.last_pid = 0;
	vars.env = init_env(env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler); // broken again ???
	return (vars);
}