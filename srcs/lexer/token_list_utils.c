#include <tokens.h>

// obsolete
int	is_token_eof(t_token *token)
{
	if (!token)
	{
		errno = ENODATA;
		exit_error(errno, "is_token_eof", NULL);
	}
	if (token->len == TOKEN_EOF)
		return (true);
	return (false);
}

t_token	*init_token(t_token *last)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(new));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "init_token", NULL);
	}
	new->next = last->next;
	new->prev = last;
	last->next = new;
	return (new);
}

void	free_token_list(t_token **ref)
{
	t_token	*i;
	t_token	*next;
	
	if (!ref || !*ref)
	{
		errno = ENOMEM;
		exit_error(errno, "free_token_list", NULL);
	}
	i = *ref;
	while (i != NULL)
	{
		if (i->text)
			free(i->text);
		next = i->next;
		free(i);
		i = next;
	}
}

t_token	*init_token_list(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "init_token_list", NULL);
	}
	new->len = TOKEN_EOF;
	return (new);
}
