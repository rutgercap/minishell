/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 11:06:51 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/18 12:13:07 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	check_char(bool *arg, bool *str, char *line)
{
	static bool	is_dubbel;
		
	if (*line == '\'' || *line == '\"')
		*str != *str;
}

static int  is_finished(char *line)
{
	static bool	arg_finished;
	static bool	str_finished;
	static int	i;

	arg_finished = true;
	str_finished = true;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			i++;
			if (!line[i])
				return (false);
		}
		else if (line[i] == )
		i++;
	}
	return ((arg_finished && str_finished));
}

char    *get_line(void)
{
	char    *more_line;
	char    *line;
	
	line = readline("minishell$ ");
	if (line && ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	while (!is_finished(line))
	{
		more_line = readline(">");
		// combine
		
	}
	add_history(line);
	return (line);
}