#include <lexer.h>

char	peek_char(t_line *line)
{
	if (line->position + 1 >= line->len)
		return (CMD_EOF);
	return (line->text[line->position + 1]);
}

char	next_char(t_line *line)
{	
	line->position++;
	if (line->position >= line->len)
		return (CMD_EOF);
	return (line->text[line->position]);
}

char	current_char(t_line *line)
{
	if (line->position >= line->len)
		return (CMD_EOF);
	return (line->text[line->position]);
}

int		skip_white_spaces(t_line *line)
{
	while (ft_isspace(peek_char(line)))
		line->position++;
	if (line->position >= line->len)
		return (CMD_EOF);
	return (EXIT_SUCCESS);
}

t_line	init_line(char *raw_line)
{
	t_line	line;

	line.len = ft_strlen(raw_line);
	line.text = raw_line;
	line.position = -1;
	return (line);
}
