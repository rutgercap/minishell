#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <parser.h>
# include <fcntl.h>

# define READ 0
# define WRITE 1
# define CHILD 0
# define NOT_FOUND -1
# define ADD_NEW -2
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
void		execute_cmd(t_cmd *cmd, t_exec *exec, t_mini_vars *vars);

// builtins
int			built_in(t_cmd *cmds, char *cmd, t_mini_vars *vars);
int			is_special_builtin(char *cmd);
int			mini_unset(char **args, t_mini_vars *vars);
int			mini_echo(char **arg, t_mini_vars *vars);
int			mini_export(char **args, t_mini_vars *vars);
char		**ft_export(char *arg, char **env, t_mini_vars *vars);
int			search_in_env(char *args, char **env, t_mini_vars *vars);
int			mini_cd(char **args, t_mini_vars *vars);
int			mini_exit(t_exec *exec, t_mini_vars *vars);
void		set_new_paths(char *new_pwd, char *old_pwd, t_mini_vars *vars);
char		*cpy_env_line(char **env, char *item);
void		mini_single_export(char **env);
void		error_message(char *arg, t_mini_vars *vars);

int			handle_forks(t_fork *new_fork, t_cmd *cmd, t_mini_vars *vars, int fd);
// redirects
int			here_doc(char *delim);
void		redirect_input(t_red *input, int fd);
void		redirect_output(t_red *output, int fd);
int			single_built_in(t_cmd *cmds, char *cmd, t_mini_vars *vars);
void		mini_single_export(char **env);
void		file_error(const char *filename);

#endif