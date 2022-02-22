/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 09:26:10 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/22 10:34:08 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static int	delim_in_line(char *line, char *delim, int len)
{
	if (!ft_strncmp(line, delim, len))
	{
		if (line[len] == '\n' && line[len + 1] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

static char	*make_text(char *delim)
{
	char	*line;
	char	*text;
	int		len;

	text = NULL;
	len = ft_strlen(delim);
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (delim_in_line(line, delim, len))
		{
			free(line);
			break ;
		}
		text = ft_strjoin_free(text, line);
	}
	// text = remove_newline(text);
	return (text);
}

int	here_doc(char *delim)
{
	char 	*text;
	int		end[2];
	// int		fd;

	if (pipe(end) < 0)
		exit_error(errno, "here_doc", NULL);
	// fd = open(end[1], O_RDONLY);
	// if (fd < 0)
	// 	file_error(end[1]);
	text = make_text(delim);
	ft_putstr_fd(text, end[1]);
	free(text);
	close(end[1]);
	return (end[0]);
}
