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

void	make_tokens(t_token *token, t_line *line)
{
	char		c;

	c = 0;
	while (true)
	{
		c = next_char(line);
		if (c == CMD_EOF)
		{
			append_to_tokens(token, TOKEN_EOF);
			break ;
		}
		process_char(token, line, c);
		while (token->next != NULL)
			token = token->next;
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

t_token	*tokenizer(char *raw_line)
{
	t_token	*tokens;
	t_line	line;

	line.text = raw_line;
	line.len = ft_strlen(line.text);	// + 1, check char_utils '>='
	line.position = -1;
	tokens = new_token(NULL, TOKEN_EOF);
	make_tokens(tokens, &line);
	return (tokens);
}
