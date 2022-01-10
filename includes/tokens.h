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
	STRING,
	PURE_STRING,
	RED_OPUT,
	RED_IPUT,
	RED_OPUT_A,
	RED_IPUT_A,
	IGNORE_EOL,
	TOKEN_EOF
}	t_type;

typedef struct s_type_char_pair {
	char	key[2];
	t_type	type;
}	t_type_chair_pair;

typedef struct s_string {
	char	*text;
	bool	pure;
	bool	finished;
}	t_string;

typedef struct s_token {
	char	*text;
	t_type	type;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef void(*t_char_func)(t_token*, t_cmd*);

/*
	char processing
*/

void	pipe_func(t_token *token, t_cmd *cmd);

void	backslash_func(t_token *token, t_cmd *cmd);

void	string_func(t_token *token, t_cmd *cmd);

void	word_func(t_token *token, t_cmd *cmd);

void	check_pairs(t_token *token, t_cmd *cmd);

/*
	general
*/

void	append_to_text(t_token *token, char c);

t_token	*new_token(t_token *last, t_type type);

void	free_token_list(t_token **ref);

t_token	*tokenize_cmd(char *line);

#endif