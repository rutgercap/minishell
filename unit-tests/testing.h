#ifndef TESTING_H
# define TESTING_H

# include <minishell.h>
# include <stdio.h>
# include <string.h>

t_token *make_token(t_type *type, char *text, t_token *last);

#endif