#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>

typedef struct s_mini_vars
{
	char	**paths;
	char	**env;
	int		*last_pid;
}	t_mini_vars;

typedef struct	s_fork
{
	pid_t			child;
	struct s_fork	*next;
}	t_fork;

void		executor(t_cmd *cmd, t_mini_vars vars);
char		**init_paths(char **env);
int			arrange_input(t_cmd *cmd, int fd, int *last_pid);
int			arrange_output(t_cmd *cmd, int write_pipe_end, int *last_pid);
t_mini_vars	init_utils(char **env, int *last_pid);
void		execute_cmd(t_cmd *cmd, t_mini_vars *utils);
int			built_in(char *word, char **arg, char **env);
int			mini_unset(char **arg, char ***env);
int			mini_echo(char **arg);
int			mini_export(char **arg, char ***env);
int			mini_exit(void);
void		free_old_env(char **env);

#endif