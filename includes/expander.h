#ifndef EXPANDER_H
# define EXPANDER_H

# define LAST_PID -1

# include <tokens.h>

void	expander(t_token *tokens, char **env, int last_pid);

#endif