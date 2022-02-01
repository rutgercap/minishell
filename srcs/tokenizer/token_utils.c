/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:31:35 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/01 16:52:13 by rcappend      ########   odam.nl         */
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

void	free_tokens(t_token **ref)
{
	t_token	*i;
	t_token	*next;
	
	if (!ref || !*ref)
	{
		errno = ENODATA;
		exit_error(errno, "free_token_list", NULL);
	}
	i = *ref;
	while (i != NULL)
	{
		next = i->next;
		delete_token(&i);
		i = next;
		if (i)
			i->prev = NULL;
	}
}

t_token	*new_token(t_token *last, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	ft_check_malloc(new, "init_token");
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->type = type;
	return (new);
}