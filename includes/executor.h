#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>

typedef struct s_utils
{
	char	**path_env;
	char	**env;
	int		last_pid;
}	t_utils;

typedef struct	s_fork_list
{
	pid_t				child;
	struct s_fork_list	*next;
}	t_fork_list;

void	executor(t_cmd *cmd, char **env, int *last_pid);
int		arrange_input(t_cmd *cmd, int fd, int *last_pid);
int		arrange_output(t_cmd *cmd, int write_pipe_end, int *last_pid);
t_utils	init_utils(char **env, int *last_pid);
void	execute_cmd(t_cmd *cmd, t_utils *utils);
int		built_in(char *word, char **arg, char **env);
int		mini_unset(char **arg, char ***env);
int		mini_echo(char **arg);
int		mini_export(char **arg, char ***env);
int		mini_exit(void);
void	free_old_env(char **env);

#endif