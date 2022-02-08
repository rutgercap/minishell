#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>
# define WRITE			1
# define READ 			0
// # define NO_VALID_FD	-1

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

char	**executor(t_cmd *cmd, char **env, int *last_pid);
int		arrange_input(t_cmd *cmd, int fd, int *last_pid);
int		arrange_output(t_cmd *cmd, int write_pipe_end, int *last_pid);
t_utils	init_utils(char **env, int *last_pid);
void	execute_cmd(t_cmd *cmd, t_utils *utils);
void	built_in(t_cmd *cmd, t_utils *utils);
void	mini_unset(char **args, char ***env, t_utils *utils);
void	mini_echo(char **args, t_utils *utils);
void	mini_export(char **args, char ***env, t_utils *utils);
void	mini_exit(void);
void	free_old_env(char **env);

#endif