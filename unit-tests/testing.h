#ifndef TESTING_H
# define TESTING_H

<<<<<<< HEAD
# include <minishell.h>
=======
# include <tokens.h>
# include <expander.h>
# include <parser.h>
>>>>>>> origin/restructure
# include <stdio.h>
# include <string.h>

t_token *make_token(t_type *type, char *text, t_token *last);

#endif