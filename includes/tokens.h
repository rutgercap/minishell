#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>

// don't reduce buff_size to 1
# define BUFF_SIZE 32
# define CMD_EOF -2

typedef enum e_type {
	WORD,
	PIPE,
	OUTPUT_S,
	OUTPUT_D,
	INPUT_S,
	INPUT_D,
	TOKEN_EOF,
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
t_token	*delete_token(t_token **ref);
void	free_tokens(t_token **ref);
int		in_string(bool s_quote, bool d_quote);
// int	check_char(char *line, int i, t_token *tokens, t_flag *flag);

/*
	special characters
*/
void	process_char(t_token *token, t_line *line, bool *s_quote, bool *d_quote);

/*
	lexing
*/
char	next_char(t_line *line);
char	current_char(t_line *line);
int		skip_white_spaces(t_line *line);
char	peek_char(t_line *line);

#endif