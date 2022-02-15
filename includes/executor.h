#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>

# define READ 0
# define WRITE 1
# define CHILD 0
# define NO_PIPE -1

/*
	Global variable that indicates if a sub-process is running
	Starts at 1
	is set to 0 if a sub-process is running
	
*/
int	g_interactive;

typedef struct s_mini_vars
{
	char	**paths;
	char	**env;
	int		last_pid;
}	t_mini_vars;

typedef struct	s_fork
{
	pid_t			pid;
	struct s_fork	*next;
}	t_fork;

void		executor(t_cmd *cmd, t_mini_vars *vars);
void		child_process(t_cmd *cmd, t_mini_vars *vars, int end[2], int input_fd);
void		execute_cmd(t_exec *exec, t_mini_vars *vars);
int			built_in(char *cmd, char **args, char **env);
int			mini_unset(char **arg, char ***env);
int			mini_echo(char **arg);
int			mini_export(char **arg, char ***env);
int			mini_exit(void);
void		free_old_env(char **env);

#endif