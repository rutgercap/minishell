/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 13:08:59 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/25 13:33:17 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars *g_vars;
char        **g_env;

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

static void	process_cmd(char *raw_line, t_mini_vars *vars)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, vars->env, vars->last_pid);
	if (!cmd)
		return ;
	executor(cmd, vars);
	free_cmd_list(&cmd);
}

void    setUp(void) {
    g_vars->env = init_env(g_env);
	g_vars->last_pid = 0;
	g_vars->paths = NULL;
}

void    tearDown(void) {
    ft_free_char_array(g_vars->env);
}

static void	assert_find(char *line, bool find) {
	bool	found = false;
	int		len = ft_strlen(line);
	char	**env;
	int		i = 0;

	env = g_vars->env;
	while (env[i])
	{
		if (!ft_strncmp(env[i], line, len)) {
			found = true;
			break ;
		}
		i++;
	}
	TEST_ASSERT(found == find);
}

static void    init_test(char *line, int expected_pid) {
    process_cmd(line, g_vars);
	TEST_ASSERT_EQUAL_INT16(expected_pid, g_vars->last_pid);
}

static void	print_env(char **env)
{
	int i = 0;

	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

static void	trial_1()
{
	init_test("export hallo=daan", 0);
	assert_find("hallo=daan", true);
}

static void	trial_2()
{
	init_test("export env_var=blablabla", 0);
	assert_find("env_var=blablabla", true);
}

static void	trial_3()
{
	init_test("export env_var=", 0);
	assert_find("env_var=", true);
}

static void	trial_4()
{
	init_test("export env_var=1", 0);
	assert_find("env_var=1", true);
}

static void	trial_5()
{
	init_test("export env_var=123456", 0);
	assert_find("env_var=123456", true);
}

int main(int argc, char **argv, char **env)
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
	return (UNITY_END());
}