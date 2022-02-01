/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 11:53:10 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/26 09:57:50 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	free_redirects(t_red *red)
{
	t_red	*next;

	while (red)
	{
		next = red->next;
		free(red->delim);
		free(red);
		red = next;
	}
}

t_red	*new_redirect(t_red_type type)
{
	t_red	*new;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "new_redirect", NULL);
	}
	new->type = type;
	return (new);
}