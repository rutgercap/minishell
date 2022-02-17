#include "testing.h"

t_mini_vars	*mini_env;
int			test_n = 0;

void	setUp(void) {

}

void	tearDown(void) {
	test_n++;
}

char	**init_env(char **env)
{
	char	**temp;
	int		len;

	len = 0;
	while (env[len])
		len++;
	temp = ft_calloc(len + 1, sizeof(char *));
	ft_check_malloc(temp, "init_env");
	while (len)
	{
		len--;
		temp[len] = ft_strdup(env[len]);
		ft_check_malloc(temp[len], "init_env");
	}
	return (temp);
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
}

void	dupdup(FILE *fd) {
	if (dup2(fileno(fd), STDOUT_FILENO)) {
		exit_error(errno, "dupdup", NULL);
	}
	if (dup2(fileno(fd), STDERR_FILENO)) {
		exit_error(errno, "dupdup", NULL);
	}
}

int	system_call(char *cmd)
{
	const char	*prefix = "/bin/bash -c \"";
	char		*temp;
	char		*full_cmd;
	int			ret;

	temp = ft_strjoin(prefix, cmd);
	full_cmd = ft_strjoin(temp, "\"");
	ret = system(full_cmd);
	free(temp);
	free(full_cmd);
	return (ret);
}

FILE	*make_file(bool bash) {
	char	file[30];
	char	*test_n_str = ft_itoa(test_n);
	FILE	*fd;

	ft_bzero(file, 30);
	ft_strcpy(file, EX_DEST, 30);
	if (bash) {
		ft_strlcat(file, "bash_", 30);
	} else {
		ft_strlcat(file, "mini_", 30);
	}
	ft_strlcat(file, test_n_str, 30);
	free(test_n_str);
	fd = fopen(file, "w+");
	if (fd == NULL) {
		exit_error(errno, "make_file", NULL);
	}
	return (fd);
}

void	test_mini(char *line) {
	process_cmd(line, mini_env);
	exit(mini_env->last_pid);
}

void	test_bash(char *line) {
	exit(system_call(line));
}

void	do_test(char *m_line, char *b_line)
{
	FILE	*mini_fd = make_file(false);
	FILE	*bash_fd = make_file(true); 
	pid_t	mini_pid, bash_pid;
	int		mini_status, bash_status;
	
	mini_pid = fork();
	if (mini_pid < 0)
		exit_error(errno,"do_test", NULL);
	else if (mini_pid == 0) {
		fclose(bash_fd);
		dupdup(mini_fd);
		test_mini(m_line); 
		return ;
	}
	bash_pid = fork();
	if (bash_pid < 0)
		exit_error(errno,"do_test", NULL);
	else if (bash_pid == 0) {
		fclose(mini_fd);
		dupdup(bash_fd);
		test_bash(b_line); 
		return ;
	}
	waitpid(mini_pid, &mini_status, 0);
	waitpid(bash_pid, &bash_status, 0);
	if (WIFEXITED(bash_status)) {
		TEST_ASSERT_EQUAL_INT16_MESSAGE(WEXITSTATUS(bash_status), WEXITSTATUS(mini_status), "exit codes not same");
	}
	fseek(mini_fd, 0L, SEEK_END);
	fseek(bash_fd, 0L, SEEK_END);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(ftell(bash_fd), ftell(mini_fd), "Outputs not same size");
	printf("%d | %d\n", WEXITSTATUS(bash_status), WEXITSTATUS(mini_status));
	fclose(mini_fd);
	fclose(bash_fd);
}

void	test_1(void) {
	do_test("lss", "lss");
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	mini_env = ft_calloc(1, sizeof(t_mini_vars));
	mini_env->env = init_env(env);
	mini_env->last_pid = 0;
	mini_env->paths = NULL;
	UNITY_BEGIN();
	test_bash("lss");
	RUN_TEST(test_1);

	return (UNITY_END());
}