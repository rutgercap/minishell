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

/*
	functions
*/
void	init_signals(void);

void	mini_exit(void);

#endif
