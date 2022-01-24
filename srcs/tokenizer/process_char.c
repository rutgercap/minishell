#include <tokens.h>

static void	append_to_text(t_token *token, char c)
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

static void	string(t_token *token, t_line *line)
{
	char	end;
	char	c;

	if (token->type != TOKEN_EOF)
	{
		token->next = new_token(token, TOKEN_EOF, "newline");
		token = token->next;
	}
	end = current_char(line);
	if (end == '\'')
		token->type = PURE_STRING;
	else
		token->type = STRING;
	while (true)
	{
		c = next_char(line);
		if (c == end)
			break ;
		else if (c == CMD_EOF)
		{
			token->next = new_token(token, ERROR, "newline");
			break ;
		}
		append_to_text(token, c);
	}
}

static void	word(t_token *token, t_line *line)
{
	char	c;

	c = current_char(line);
	if (token->type == TOKEN_EOF)
		token->type = WORD;
	else if (token->type != WORD)
	{
		token->next = new_token(token, WORD, NULL);
		token = token->next;
	}
	append_to_text(token, c);
}

void	process_char(t_token *token, t_line *line, char c)
{	
	if (ft_isspace(c))
	{
		skip_white_spaces(line);
		append_to_tokens(token, TOKEN_EOF);
	}
	else if (c == '>')
		append_to_tokens(token, IPUT_BRACK);
	else if (c == '<')
		append_to_tokens(token, OPUT_BRACK);
	else if (c == '|')
		append_to_tokens(token, PIPE);
	else if (c == '\'' || c == '\"')
		string(token, line);
	else
		word(token, line);
}