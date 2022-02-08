#ifndef TESTING_H
# define TESTING_H

# include <tokens.h>
# include <expander.h>
# include <parser.h>
# include <stdio.h>
# include <string.h>
# include <unity.h>

t_token *make_token(t_type *type, char *text, t_token *last);
void	lextester1(void);

#endif
