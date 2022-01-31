#include <tokens.h>

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
		free(i->text);
		next = i->next;
		free(i);
		i = next;
	}
}

void	append_to_tokens(t_token *last, t_type type)
{	
	if (last->type == TOKEN_EOF)
		last->type = type;
	else
		last->next = new_token(last, type);
}

t_token	*new_token(t_token *last, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	ft_check_malloc(new, "new_token");
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->type = type;
	return (new);
}

t_token	*tokenizer(char *line)
{
	t_token	*tokens;
	t_flag	*flag;
	int		i;

	tokens = NULL;
	flag = (t_flag *)malloc(1 * sizeof(t_flag));
	*flag = NORMAL;
	i = 0;
	while (line[i])
	{
		i = check_char(line, i, tokens, flag);
	}
	return (tokens);
}
