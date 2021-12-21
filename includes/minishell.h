#ifndef MINISHELL_H
# define MINISHELL_H

/*
	minishell libraries
*/
# include <executor.h>
# include <parser.h>
# include <utils.h>

/*
	standard c libraries
*/
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

/*
	defines and typedefs
*/
typedef struct sigaction t_sigaction;

/*
	functions
*/
void	init_sigactions(void);

#endif
