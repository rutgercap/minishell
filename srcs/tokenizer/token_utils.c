/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:31:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/26 10:38:45 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>

t_token	*delete_token(t_token **ref)
{
	t_token	*i;
	t_token	*prev;
	t_token	*next;

	if (!ref || !*ref)
	{
		errno = ENODATA;
		exit_error(errno, "delete token", NULL);
	}
	i = *ref;
	next = i->next;
	prev = i->prev;
	if (prev)
		prev->next = i->next;
	free(i->text);
	free(i);
	if (prev)
		return (prev);
	return (next);
}