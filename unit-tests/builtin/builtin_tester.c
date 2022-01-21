#include "builtin_tester.h"

static void	tester_unset(char **env, char *test)
{
	char	**arg;
	int		i;

	i = 0;
	printf("-----------------OLD ENV:\n\n");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	arg = ft_split(test, ' ');
	mini_unset(arg, env);
	printf("\nNEW ENV:\n\n");
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return ;
}

static void	tester_builtin(char **env)
{
	// tester_echo(env);

	// tester_cd(env);

	// tester_pwd(env);
	
	// tester_export(env);

	tester_unset(env, "HOME PATH");

	// tester_env(env);

	// tester_exit(env);

	return ;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	tester_builtin(env);
}