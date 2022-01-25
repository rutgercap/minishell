#ifndef PARSER_H
# define PARSER_H

# include <utils.h>
# include <tokens.h>

# define SYNTAX_ERROR -1

typedef enum e_red_type {
	UNDEFINED,
	RED_PIPE,
	RED_IPUT,
	HERE_DOC,
	RED_OPUT,
	RED_OPUT_A,
}   t_red_type;

typedef struct s_red {
	t_red_type		type;
	char			*delim;
	struct s_red	*next;
}	t_red;

typedef struct s_cmd {
	char			*command;
	char			**arguments;
	t_red			*input;
	t_red			*output;
	struct s_cmd	*next;
}   t_cmd;


/*
	command list utils
*/
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd **cmd);
void	free_cmd_list(t_cmd **ref);

/*
	redirects list utils
*/
void	free_redirects(t_red *red);
t_red	*new_redirect(t_red_type type);

/*
	main
*/
int		parse_redirects(t_cmd *cmd_list, t_token *tokens);
int		syntax_error(t_token *token);
t_cmd	*parser(t_token *tokens);

#endif
