/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/02 08:45:51 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

int		g_last_pid;
char	**g_env;
t_token *tokens;
t_token *i;

static void	init_test(char *line)
{
	tokens = tokenizer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	i = tokens;
    parser(i, g_env, g_last_pid);
}

static void		assert_token(t_type type, char *text)
{
	long	len;

	TEST_ASSERT_NOT_NULL(i);
	TEST_ASSERT_EQUAL_INT16(type, i->type);
	if (!text)
	{
		TEST_ASSERT_NULL(i->text);
		i->len = 0;
	}
	else
	{
		len = strlen(text);
		TEST_ASSERT_EQUAL_STRING(text, i->text);
		TEST_ASSERT_EQUAL_UINT64(len, i->len);
	}
	i = i->next;
}

void setUp(void) {
    
}

void tearDown(void) {
    assert_token(TOKEN_EOF, NULL);
	free_tokens(&tokens);
	tokens = NULL;
	i = NULL;
}

static void	trial_1()
{
	init_test("  test  ");
	assert_token(WORD, "test");
}

static void	trial_2()
{
	init_test("  test  test test  test test test       test     test    test ");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
	assert_token(WORD, "test");
}

static void	trial_3()
{
	init_test("      ");
}

static void	trial_4()
{
	init_test("");
}

static void	trial_5()
{
	init_test(" ls -l");
	assert_token(WORD, "ls");
	assert_token(WORD, "-l");
}

static void	trial_6()
{
	init_test("echo \"string\" hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "string");
	assert_token(WORD, "hi");
}

static void	trial_7()
{
	init_test("echo hi\"string\"hi");
	assert_token(WORD, "echo");
	assert_token(WORD, "histringhi");
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
	g_env = env;
	g_last_pid = 42;
    UNITY_BEGIN();
	RUN_TEST(trial_1);
    RUN_TEST(trial_2);
    RUN_TEST(trial_3);
    RUN_TEST(trial_4);
    RUN_TEST(trial_5);
	RUN_TEST(trial_6);
	trial_6();
	RUN_TEST(trial_7);
    return (UNITY_END());
}
