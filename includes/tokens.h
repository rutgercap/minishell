#ifndef TOKENS_H
# define TOKENS_H

# include <utils.h>
# include <lexer.h>

// Think it breaks if buff_size reduced to 1
# define BUFF_SIZE 32
# define TOKEN_EOF -1

typedef enum e_type {
	word,
	e_pipe,
	red_oput,	// redirect output
	red_iput,	// redirect input
	red_oput_a,	// redirect output + append
	red_iput_a	// not sure what this does
} t_type;

typedef struct s_token {
	char	*text;
	t_type	type;
	long	len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	add_to_end(t_token **ref, t_token *new);

t_token	*init_token(t_token *next);

t_token	*init_token_list(void);

t_token	*tokenize_cmd(char *line);

#endif