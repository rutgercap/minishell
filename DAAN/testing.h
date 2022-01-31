#ifndef HEADERS_H
# define HEADERS_H

# include <tokens.h>
# include <expander.h>
# include <parser.h>
# include <stdio.h>

void	write_type(t_type type);

void	write_token(t_token *token);

void	write_all_tokens(t_token *tokens);

#endif