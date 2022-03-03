/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 13:41:39 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 13:41:39 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	minishell libraries
*/
# include <builtins.h>
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
# define INTERACT 1
# define NO_INTERACT 0

/*
	functions
*/
void	init_signals(void);
void	sigquit_handler(int signum);

#endif
