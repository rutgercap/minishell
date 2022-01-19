#ifndef LEXER_H
# define LEXER_H

# include <utils.h>

# define CMD_EOF -2

typedef struct s_line {
	char	*text;
	long	len;
	long	position;
}	t_line;

/*
	main functions
*/
char	next_char(t_line *line);

char	current_char(t_line *line);

int		skip_white_spaces(t_line *line);

char	peek_char(t_line *line);

t_line	init_line(char *raw_line);

#endif
