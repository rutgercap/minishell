#ifndef MINISHELL_H
# define MINISHELL_H

/*
	minishell libraries
*/
# include <executor.h>
# include <parser.h>
# include <tokens.h>
# include <utils.h>

/*
	standard c libraries
*/
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

/*
	Defines and typedefs
*/
# define CTRL_D 64

/*
	functions
*/
t_mini_vars	init_minishell(char **env);

#endif
