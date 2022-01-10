#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define CMD_EOF -2

typedef struct s_cmd {
	char	*line;
	long	len;
	long	position;
}	t_cmd;

/*
	utils
*/
int		input_check(const void *to_check, char *func);

int		is_delimiter(char c);

/*
	main functions
*/
char	next_char(t_cmd *cmd);

char	current_char(t_cmd *cmd);

int		skip_white_spaces(t_cmd *cmd);

char	peek_char(t_cmd *cmd);

t_cmd	init_cmd(char *raw_line);

#endif
