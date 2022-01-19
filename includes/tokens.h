#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>
# include <lexer.h>

// breaks if reduced to 1
# define BUFF_SIZE 32

typedef enum e_type {
	WORD,
	PIPE,
	STRING,
	PURE_STRING,
	RED_OPUT,
	RED_IPUT,
	TOKEN_EOF
}	t_type;

typedef struct s_token {
	t_type	type;
	char	*text;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*
	general
*/
void	append_to_text(t_token *token, char c);

t_token	*new_token(t_token *last, t_type type);

void	append_to_tokens(t_token *last, t_type type);

void	free_token_list(t_token **ref);

t_token	*tokenize_cmd(char *line);

#endif