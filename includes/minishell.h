#ifndef MINISHELL_H
# define MINISHELL_H

/*
	minishell libraries
*/
# include <executor.h>
# include <expander.h>
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
	Global variable that indicates if a sub-process is running
	Starts at 1
	is set to 0 if a sub-process is running
	
*/
int	g_interactive;

/*
	functions
*/
void	init_signals(void);

int		mini_exit(void);

#endif
