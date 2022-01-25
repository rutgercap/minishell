#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <utils.h>

/*
	built_in
*/
void	built_in(char *word, char **arg, char **env);
void	mini_unset(char **arg, char ***env);
void	mini_echo(char **arg);
void	mini_export(char **arg, char ***env);
void	free_old_env(char **env);

#endif
