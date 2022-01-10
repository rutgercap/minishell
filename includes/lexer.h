#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define CMD_EOF -2

typedef struct s_cmd {
	char	*line;
	long	len;
	long	position;
}	t_cmd;

char	next_char(t_cmd *cmd);

int		skip_white_spaces(t_cmd *cmd);

char	peek_char(t_cmd *cmd);

void	special_character(t_token *token, t_cmd *cmd);

t_cmd	init_cmd(char *raw_line);

#endif
