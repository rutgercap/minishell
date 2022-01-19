#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>

# define BUFF_SIZE 32
# define CMD_EOF -2

typedef enum e_type {
	WORD,
	SPACE,
	PIPE,
	STRING,
	PURE_STRING,
	RED_OPUT,
	RED_IPUT,
	TOKEN_EOF,
	ERROR
}	t_type;

typedef struct s_token {
	t_type	type;
	char	*text;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_line {
	char	*text;
	long	len;
	long	position;
}	t_line;

/*
	tokens
*/
t_token	*tokenizer(char *raw_line);
t_token	*new_token(t_token *last, t_type type);
void	make_tokens(t_token *token, t_line *line);
void	append_to_tokens(t_token *last, t_type type);
void	free_tokens(t_token **ref);

/*
	special characters
*/
void	process_char(t_token *token, t_line *line, char c);

/*
	lexing
*/
char	next_char(t_line *line);
char	current_char(t_line *line);
int		skip_white_spaces(t_line *line);
char	peek_char(t_line *line);

#endif