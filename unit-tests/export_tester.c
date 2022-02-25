/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/25 12:47:40 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars	*g_vars;
char		**g_env;

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
	g_vars->env = init_env(g_env);
	g_vars->last_pid = 0;
	g_vars->paths = NULL;
}

void	print_env(char **env)
{
	int i = 0;

	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void    tearDown(void)
{
	ft_free_char_array(g_vars->env);
}

static void	new_test(char *line, int expected, int expected_pid)
{
	int	row;
	
	row = search_in_env(line, g_vars->env, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected, row);
	g_vars->env = ft_export(line, g_vars->env, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected_pid, g_vars->last_pid);
	row = search_in_env(line, g_vars->env, g_vars);
	TEST_ASSERT(row >= 0);
	TEST_ASSERT_EQUAL_STRING(line, g_vars->env[row]);
}

static void	adjust_test(char *line, int expected_pid)
{
	int	row;
	int	n_row;

	row = search_in_env(line, g_vars->env, g_vars);
	g_vars->env = ft_export(line, g_vars->env, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected_pid, g_vars->last_pid);
	n_row = search_in_env(line, g_env, g_vars);
	TEST_ASSERT_EQUAL_INT16(row, n_row);
	TEST_ASSERT_EQUAL_STRING(line, g_vars->env[n_row]);
}

static void	error_test(char *line, char *old, int expected_pid)
{
	int row;

	if (old) {
		row = search_in_env(line, g_vars->env, g_vars);
	}
	g_vars->env = ft_export(line, g_vars->env, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected_pid, g_vars->last_pid);
	if (old) {
		TEST_ASSERT_EQUAL_STRING(old, g_vars->env[row]);
	}
}

static void	trial_1()
{
	new_test("hallo=daan", -2, 0);
}

static void	trial_2()
{
	adjust_test("env_var=blablabla", 0);
}

static void	trial_3()
{
	error_test("env_var=!", "env_var=blabla", 1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
    (void)argv;
	g_vars = ft_calloc(1, sizeof(t_mini_vars));
	if (!g_vars) {
		exit(-1);
	}
	g_env = init_env(env);
	UNITY_BEGIN();
	RUN_TEST(trial_1);
	RUN_TEST(trial_2);
	RUN_TEST(trial_3);
	return UNITY_END();
}