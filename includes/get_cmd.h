#ifndef GET_CMD_H
# define GET_CMD_H

# include <utils.h>
# include <stdio.h>
# include <errno.h>

# define ERROR (ssize_t)-1

int		get_cmd(char **dest);

#endif