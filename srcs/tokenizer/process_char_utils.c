/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_char_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 12:20:07 by rcappend      #+#    #+#                 */
/*   Updated: 2022/03/03 12:20:42 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

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

int	skip_white_spaces(t_line *line)
{
	while (ft_isspace(peek_char(line)))
		line->position++;
	if (line->position >= line->len)
		return (CMD_EOF);
	return (EXIT_SUCCESS);
}
