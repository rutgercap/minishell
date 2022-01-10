#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>
# include <lexer.h>

// breaks if reduced to 1
# define BUFF_SIZE 32

typedef enum e_type {
	WORD,
	PIPE,
	RED_OPUT,	// redirect output
	RED_IPUT,	// redirect input
	RED_OPUT_A,	// redirect output + append
	RED_IPUT_A,	// not sure what this does
	IGNORE_EOL,
	TOKEN_EOF
}	t_type;

typedef struct s_token {
	char	*text;
	t_type	type;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	append_to_text(t_token *token, char c);

t_token	*new_token(t_token *last, t_type type);

void	free_token_list(t_token **ref);

t_token	*tokenize_cmd(char *line);

#endif