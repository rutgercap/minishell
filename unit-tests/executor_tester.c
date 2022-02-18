#include "testing.h"

t_mini_vars	*mini_env;
char		*m_file_path = "results/executor/mini_";
char		*b_file_path = "results/executor/bash_";
FILE		*m_fs;
FILE		*b_fs;
int			test_n = 0;
int			sig;

void	setUp(void) {
	sig = 0;
	mini_env->last_pid = 0;
	m_file_path = ft_strjoin(m_file_path, ft_itoa(test_n));
	b_file_path = ft_strjoin(b_file_path, ft_itoa(test_n));
	m_fs = fopen(m_file_path, "w+");
	b_fs = fopen(b_file_path, "w+");
	if (!m_fs || !b_fs) {
		exit_error(errno, "making files", NULL);
	}
}

void	tearDown(void) {
	test_n++;
	free(m_file_path);
	free(b_file_path);
	m_file_path = ft_strdup("results/executor/mini_");
	b_file_path = ft_strdup("results/executor/bash_");
	fclose(b_fs); fclose(m_fs);
}

// hierin gaat alle test logica nadat files zijn geopend en er is gedup'd
void	test_mini(char *line) {
	process_cmd(line, mini_env);
	exit(mini_env->last_pid);
}

// gekopieerd uit minishell
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

// gekopieerd uit minishell maar zonder signals
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

// deze gat nog mis
void	dupdup(FILE *fd) {
	if (dup2(fileno(fd), STDOUT_FILENO) < 0) {
		exit_error(errno, "dupdup", NULL);
	}
	if (dup2(fileno(fd), STDERR_FILENO) < 0) {
		exit_error(errno, "dupdup", NULL);
	}
	fclose(fd);
}

// hierin gaat command en roept een bash system call op
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

void	compare_file_size(FILE *fs1, FILE *fs2) {
	fseek(fs1, 0L, SEEK_END);
	fseek(fs2, 0L, SEEK_END);
	TEST_ASSERT_EQUAL_INT16_MESSAGE(ftell(fs1), ftell(fs2), "Outputs not same size");
}

void	compare_exit_codes(int mini_status, int bash_status) {
	if (WEXITSTATUS(mini_status) || WEXITSTATUS(bash_status)) {
		TEST_ASSERT_EQUAL_INT16_MESSAGE(WEXITSTATUS(mini_status), WEXITSTATUS(bash_status), "Exit codes not same");
	} else if (WIFSIGNALED(mini_status)) {
		TEST_ASSERT_EQUAL_INT16_MESSAGE(sig, WTERMSIG(mini_status) + 128, "Exit codes not same");
	}
}

void	assert_file(char *m_file, char *b_file) {
	FILE	*m_file_fs, *b_file_fs;
	
	TEST_ASSERT(!access(m_file, R_OK));
	TEST_ASSERT_MESSAGE(!access(b_file, R_OK), "file was found, but shouldn't have been made");
	m_file_fs = fopen(m_file, "r"); b_file_fs = fopen(b_file, "r");
	compare_file_size(m_file_fs, b_file_fs);
	fclose(m_file_fs); fclose(b_file_fs);
	remove(m_file); remove(b_file);
}

void	do_test(char *m_line, char *b_line)
{
	pid_t	mini_pid, bash_pid;
	int		mini_status, bash_status;
	
	mini_pid = fork();
	if (mini_pid < 0)
		exit_error(errno,"do_test", NULL);
	else if (mini_pid == 0) {
		fclose(b_fs);
		dupdup(m_fs);
		test_mini(m_line);
		exit(mini_env->last_pid);
	}
	bash_pid = fork();
	if (bash_pid < 0)
		exit_error(errno,"do_test", NULL);
	else if (bash_pid == 0) {
		fclose(m_fs);
		dupdup(b_fs);
		exit(system_call(b_line));
	}
	waitpid(mini_pid, &mini_status, 0);
	waitpid(bash_pid, &bash_status, 0);
	compare_exit_codes(mini_pid, bash_pid);
	compare_file_size(m_fs, b_fs);
	fclose(m_fs);
	fclose(b_fs);
}

void	remove_files(void) {
	remove(b_file_path);
	remove(m_file_path);
}

void	test_1(void) {
	do_test("ls", "ls");
	remove_files();
}

void	test_2(void) {
	do_test("lss", "lss");
	remove_files();
}

void	test_3(void) {
	do_test("ls > results/file1", "ls > results/file2");
	assert_file("results/file1", "results/file2");
	remove_files();
}

void	test_4(void) {
	do_test("> results/file1", "> results/file2");
	assert_file("results/file1", "results/file2");
	remove_files();
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
	RUN_TEST(test_1);
	RUN_TEST(test_2);
	RUN_TEST(test_3);
	return (UNITY_END());
}