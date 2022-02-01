#ifndef EXPANDER_H
# define EXPANDER_H

# define EXPANDED 1
# define NO_EXPAND 0

# include <tokens.h>

int expander(t_token *token, char **env, int last_pid, long i);

#endif