#include "builtin_tester.h"

static char **copy_env(char **env)
{
	char	**new_env;
	int		i;
	int		len;
	int		size;

	size = 0;
	while (env[size])
		size++;
	new_env = (char **)malloc(((size + 1) * sizeof(char *)));
	i = 0;
	while (i < size)
	{
		len = ft_strlen(env[i]);
		new_env[i] = (char *)ft_calloc(len + 1, sizeof(char));
		ft_strcpy(new_env[i], env[i], len);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	tester_unset(char **env, char *test)
{
	char	**arg;
	char	**new_env;
	int		i;

	new_env = copy_env(env);
	arg = ft_split(test, ' ');
	mini_unset(arg, &new_env);
	i = 0;
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	return ;
}
