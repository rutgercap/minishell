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
# include <stdlib.h>

/*
	defines and typedefs
*/

# define CTRL_D 26

/*
	functions
*/
void	init_signals(void);

void	mini_exit(void);

#endif
