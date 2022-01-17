#ifndef PARSER_H
# define PARSER_H

# include <utils.h>

typedef enum e_red_types {
	NORMAL,
	IPUT,
	OPUT,
	HERE_DOC,
	OPUT_APPEND
}   t_red_types;

typedef struct s_red {
	t_red_types type;
	char        *location;
}   t_red;

typedef struct s_cmd {
	char    *name;
	char    *arguments;
	char    *combined;  // voor execve?
	t_red   input;
	t_red	output;
}   t_cmd;

typedef struct s_ast {
	t_pipe_input	input;
}   t_ast;

typedef union u_pipe_input {
	union u_pipe_input	pipe_input;
	t_cmd				cmd;
}	t_pipe_input;

#endif