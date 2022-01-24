#ifndef PARSER_H
# define PARSER_H

# include <utils.h>
# include <tokens.h>

typedef enum e_red_type {
	DEFAULT,
	RED_OPUT,
	RED_IPUT,
	RED_IPUT_A,
	HERE_DOC,
	ERROR
}   t_red_type;

typedef struct s_red {
	t_red_type	type;
	char		*delim;
}	t_red;

typedef struct s_cmd {
	char			*command;
	char			**arguments;
	t_red			input;
	t_red			output;
	struct t_cmd	*next;
}   t_cmd;

// t_pipe

/*

typedef struct s_ast {
	t_cmd	*cmds;

}	t_ast;

*/
#endif
