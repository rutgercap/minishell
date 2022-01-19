#ifndef PARSER_H
# define PARSER_H

# include <utils.h>
# include <tokens.h>

typedef struct s_cmd {
    char    *function;
    char    **arguments;
    t_red   redirects;
}   t_cmd;

typedef struct s_red_type {
    RED_IPUT,
    RED_OPUT,
    RED_IPUT_A,
    HERE_DOC
}   t_red_type;

typedef struct s_red {
    int fd_in;
    int fd_out;
}   t_red;

#endif