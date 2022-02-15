/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_tester.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:10:47 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/15 10:32:51 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_mini_vars	vars;
int			test_n = 0;

static char	*make_command(char *file_1, char *file_2, char *diff_file)
{
	char	*str_1;
	char	*str_2;
	char	*prefix = "diff ";
	char	*suffix = " > ";

	str_1 = ft_strjoin(prefix, file_1);
	str_2 = ft_strjoin(str_1, " ");
	free(str_1);
	str_1 = ft_strjoin(str_2, file_2);
	free(str_2);
	str_2 = ft_strjoin(str_1, suffix);
	free(str_1);
	str_1 = ft_strjoin(str_2, diff_file);
	free(str_2);
	return (str_1);
}

static int		get_file_size(const char *diff_file)
{
	int		file_size;
	FILE	*fp;
	
	fp = fopen(diff_file, "r");
	if (!fp)
	{
		perror("get_file_size");
		exit(errno);
	}
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	fclose(fp);
	return (file_size);
}

void	diff_file(char *mini_file, char *bash_file)
{
	char	*full_command;
	char	*diff_file = "results/diff/diff_";
	int		file_size;
	
	mini_file = ft_strjoin("results/", mini_file);
	bash_file = ft_strjoin("results/", bash_file);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(0, access(mini_file, R_OK), "access_mini_file");
	TEST_ASSERT_EQUAL_INT16_MESSAGE(0, access(bash_file, R_OK), "access_bash_file");
	diff_file = ft_strjoin(diff_file, ft_itoa(test_n));
	full_command = make_command(mini_file, bash_file,diff_file);
	system(full_command);
	free(full_command);
	file_size = get_file_size(diff_file);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(0, file_size, "diff_file_size");
	if (file_size == 0) {
		if (remove(diff_file))
		{
			perror("remove file");
			exit(errno);
		}
	}
	printf("%s\n", mini_file);
	if (remove(mini_file))
	{
		perror("remove minifile");
		exit(errno);
	}
	if (remove(bash_file))
	{
		perror("remove bashfile");
		exit(errno);
	}
	free(diff_file);
	free(mini_file);
	free(bash_file);
}

void	process_cmd(char *raw_line, t_mini_vars *vars)
{
	t_token	*tokens;
	t_cmd	*cmd;
	
	tokens = tokenizer(raw_line);
	cmd = parser(tokens, vars->env, vars->last_pid);
	if (!cmd)
		return ;
	executor(cmd, vars);
	free_cmd_list(&cmd);
	if (!ft_strncmp(raw_line, "exit", 4))
		mini_exit();
}

void    setUp(void)
{
    
}

void    tearDown(void)
{
    test_n++;
}

void	init_test(char *mini_line, char *bash_line)
{
	process_cmd(mini_line, &vars);
	system(bash_line);
}

void	trial_1(void)
{
	init_test("echo hi > results/mini1", "echo hi > results/bash1");
	diff_file("mini1", "bash1");
}

void	trial_2(void)
{
	init_test("ls > results/mini2 > results/mini3 | ls >> results/mini3",\
	 "ls > results/bash2 > results/bash3 | ls >> results/mini3");
	diff_file("mini1", "bash1");
	diff_file("mini2", "bash2");
	diff_file("mini3", "bash3");
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	vars.env = init_env(env);
	UNITY_BEGIN();
	RUN_TEST(trial_1);
	RUN_TEST(trial_2);
	return (UNITY_END());
}