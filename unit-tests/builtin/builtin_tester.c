#include "builtin_tester.h"	

static void	tester_builtin(char **env)
{
	/* echo tester */
	// ft_putendl_fd("TESTER_ECHO\ntest1:", STDOUT_FILENO);
	// tester_echo(env, "hallo ik ben $USER");
	// ft_putendl_fd("piekeboe", STDOUT_FILENO);
	// tester_echo(env, "-n hallo ik ben $USER");
	// ft_putendl_fd("piekeboe", STDOUT_FILENO);
	// ft_putendl_fd("----------------------", STDOUT_FILENO);

	// tester_cd(env);

	// tester_pwd(env);
	
	tester_export(env, "HOME=daan USER=hallo");

	/* unset tester */
	// tester_unset(env, "ietsPAGER less HOME TERMks");

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
