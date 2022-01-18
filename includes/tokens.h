#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>
# include <lexer.h>

// breaks if reduced to 1
# define BUFF_SIZE 32

typedef enum e_type {
	WORD,
	PIPE,
	DELIM,
	ARG,
	STRING,
	PURE_STRING,
	RED_OPUT,
	RED_IPUT,
	RED_OPUT_A,
	RED_IPUT_A,
	IGNORE_EOL,
	TOKEN_EOF
}	t_type;

typedef struct s_string {
	char	*text;
	bool	pure;
	bool	finished;
}	t_string;

typedef struct s_token {
	t_type	type;
	char	*text;
	bool	finished;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef void(*t_char_func)(t_token*, t_cmd*);

/*
	special characters
*/

void	backslash_func(t_token *token, t_cmd *cmd);

void	pure_string(t_token *token, t_cmd *cmd);

void	normal_string(t_token *token, t_cmd *cmd);

void	check_redirect(t_token *token, t_cmd *cmd);

void	check_single(t_token *token, t_cmd *cmd);

void	arg_function(t_token *token, t_cmd *cmd);

/*
	general
*/

void	append_to_text(t_token *token, char c);

t_token	*new_token(t_token *last, t_type type);

void	add_eof_token(t_token **token, t_cmd *cmd,
		t_char_func *func);

void	free_token_list(t_token **ref);

t_token	*tokenize_cmd(char *line);

#endif