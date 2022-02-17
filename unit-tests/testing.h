#ifndef TESTING_H
# define TESTING_H

# include <minishell.h>
# include <stdio.h>
# include <string.h>
# include <unity.h>

#ifndef EX_DEST
# define EX_DEST "results/executor/"
#endif

char	**init_env(char **env);

void	process_cmd(char *raw_line, t_mini_vars *vars);

#endif
