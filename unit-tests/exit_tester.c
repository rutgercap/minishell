/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_tester.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 16:13:45 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/21 16:36:58 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars *vars;
int         expected;
int         actual;

void setUp() {
    vars->last_pid = 0;
    expected = 0;
}

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

void    assert_output(char *expected) {
    char    *actual;

    actual = get_next_line(STDIN_FILENO);
    TEST_ASSERT_EQUAL_STRING(expected, actual);
    free(actual);
}

void tearDown() {
    TEST_ASSERT_EQUAL_INT16(expected, actual);
    assert_output(NULL);
}

void    wait_for_exit(pid_t pid) {
    waitpid(pid, &actual, 0);
    if (WIFEXITED(actual))
		vars->last_pid = WEXITSTATUS(actual);
}

void    assert_last_pid(int expected_pid) {
    TEST_ASSERT_EQUAL_INT16(expected_pid, vars->last_pid);
}

void    init_test(char *line)
{
    char    **args = ft_split(line, '+');
    pid_t   pid;
    int     end[2];

    pid = fork();
    if (pipe(end) < 0) {
        exit_error(errno, "init_test", NULL);
    }
    if (pid < 0) {
        exit_error(errno, "init_test", NULL);
    } else if (pid == CHILD) {
        dup2(end[WRITE], STDERR_FILENO);
        dup2(end[WRITE], STDIN_FILENO);
        close(end[READ]);
        mini_exit(args, vars);
        exit(-1);
    } else {
        dup2(end[READ], STDIN_FILENO);
        close(end[WRITE]);
    }
    wait_for_exit(pid);
    ft_free_char_array(args);
}

void    test_1() {
    init_test("exit");
    assert_output("exit");
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    vars->env = init_env(env);
    vars->last_pid = 0;
    vars->paths = NULL;
    UNITY_BEGIN();
    RUN_TEST(test_1);
    return (UNITY_END());
}