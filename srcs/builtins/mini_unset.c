#include "builtin.h"

static char	**edit_env_unset(char **env, int exl_row)
{
	char	**new_env;
	int		size;
	int		env_i;
	int		new_env_i;

	size = 0;
	while (env[size])
		size++;
	new_env = (char **)malloc((size - 1) * sizeof(char *));
	env_i = 0;
	new_env_i = 0;
	while (env_i < size)
	{
		if (env_i == exl_row)
			env_i++;
		ft_strlcpy(new_env[new_env_i], env[env_i], ft_strlen(env[env_i]));
		env_i++;
		new_env_i++;
	}
	return (new_env);
}

static void	check_in_env_unset(char *arg, char **env)
{
	int	i;
	int	len;

	len = ft_strlen(arg);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0)
			env = edit_env_unset(env, i);						// env persoonlijk maken
		i++;
	}
	return ;
}

void	mini_unset(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		check_in_env_unset(arg[i], env);
		i++;
	}
}