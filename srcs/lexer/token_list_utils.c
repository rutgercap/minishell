#include <tokens.h>

void	append_to_text(t_token *token, char c)
{
	char	*new;

	if (token->len + 1 % BUFF_SIZE == 1)
	{
		new = ft_calloc(token->len + BUFF_SIZE + 1, 1);
		if (!new)
		{
			errno = ENOMEM;
			exit_error(errno, "append_to_text", NULL);
		}
		ft_strcpy(new, token->text, token->len);
		free(token->text);
		token->text = new;
	}
	token->text[token->len] = c;
	token->len++;
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
		free(i->text);
		next = i->next;
		free(i);
		i = next;
	}
}

t_token	*new_token(t_token *last, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "init_token", NULL);
	}
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->type = type;
	return (new);
}