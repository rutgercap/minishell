#include <tokens.h>


static int	is_delimiter(char c)
{
	return ((c == ';' || c == '&' || c == '|') 
		|| ft_isspace(c));
}

static int	is_special_char(char c)
{
	return ((c == '|' || c == '>' || c == '<' || c == '\\'));
}

void	append_to_text(t_token *token, char c)
{
	char	*new;

	if (token->len + 1 % BUFF_SIZE == 1)
	{
		new = ft_calloc(token->len + BUFF_SIZE, 1);
		if (!new)
		{
			errno = ENOMEM;
			exit_error(errno, "append_to_text", NULL);
		}
		ft_strcpy(new, token->text, token->len);
		free(token->text);
		token->text = new;
	}
	token->len++;
	token->text[token->len] = c;
}

static void	process_char(t_token *token, char c)
{
	if (is_special_char(c))	
		return ;
	else
		append_to_text(token, c);
}

void	make_token(t_token *token, t_cmd *cmd)
{
	t_token	*new;
	char	c;

	c = 0;
	while (!is_delimiter(c))
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
			break ;
		else if (is_delimiter(c))
			break ;
		new = init_token(token);
		process_char(new, c);
	}
}

t_token	**tokenize_cmd(char *line)
{
	t_token	**tokens;
	t_token	*i;
	t_cmd	cmd;

	*tokens = init_token_list();
	i = *tokens;
	cmd = init_cmd(line);
	while (cmd.position < cmd.len)
	{
		if (skip_white_spaces(&cmd) == CMD_EOF)
			break ;
		make_token(i, &cmd);
		i = i->next;
	}
	return (tokens);
}
