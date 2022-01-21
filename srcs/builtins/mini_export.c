#include "builtin.h"

static void	edit_env_export(char *env)
{
	
}
static void	check_in_env_export(char *arg, char **env)
{
	int	i;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0)
			edit_env_export(env[i]);						// env persoonlijk maken
		i++;
	}
	return (0);
}

void	mini_export(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		check_in_env_export(arg[i], env);
		i++;
	}
}
