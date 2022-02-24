/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_tester.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/14 12:06:59 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars	*vars;
char		**myenv;
char		**args;
int			row;


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

void    setUp(void)
{  
	vars->env = init_env(myenv);
	vars->last_pid = 0;
	vars->paths = NULL;
}

void    tearDown(void)
{
	ft_free_char_array(args);
	ft_free_char_array(vars->env);
}

static void	init_test(char *line)
{
	row = search_in_env(line, vars->env, vars);
	vars->env = ft_export(line, vars->env, vars);
}

static void	trial_1()
{
	args = ft_split("export hallo=daan", ' ');
	init_test(args[1]);
	TEST_ASSERT_EQUAL_INT16(-2, row);
	row = search_in_env(args[1], vars->env, vars);
	TEST_ASSERT_EQUAL_STRING(args[1], vars->env[row]);
}
int	main(int argc, char **argv, char **env)
{
	(void)argc;
    (void)argv;
	ft_putendl_fd(env[1], 2);
	myenv = env;
	UNITY_BEGIN();
	RUN_TEST(trial_1);
	return UNITY_END();
}