#include <tokens.h>

static void	string(t_token *token, t_cmd *cmd)
{
	char	end;
	char	c;

	end = current_char(cmd);
	if (end == '\'')
		token->type = PURE_STRING;
	else
		token->type = STRING;
	while (true)
	{
		c = next_char(cmd);
		if (c == end)
			break ;
		else if (c == CMD_EOF)
		{
			errno = EINVAL;
			exit_error(errno, "string", NULL);
		}
		append_to_text(token, c);
	}
}

static void	word(t_token *token, t_cmd *cmd)
{
	char	c;

	c = current_char(cmd);
	if (token->type == TOKEN_EOF)
		token->type = WORD;
	else if (token->type != WORD)
	{
		token->next = new_token(token, WORD);
		token = token->next;
	}
	append_to_text(token, c);
}

static void	process_char(t_token *token, t_cmd *cmd, char c)
{	
	if (ft_isspace(c))
	{
		skip_white_spaces(cmd);
		append_to_tokens(token, TOKEN_EOF);
		return ;
	}
	else if (c == '>')
		append_to_tokens(token, RED_OPUT);
	else if (c == '<')
		append_to_tokens(token, RED_IPUT);
	else if (c == '|')
		append_to_tokens(token, PIPE);
	else if (c == '\'' || c == '\"')
		string(token, cmd);
	else
		word(token, cmd);
}

static void	make_tokens(t_token *token, t_cmd *cmd)
{
	char		c;

	c = 0;
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
		{
			append_to_tokens(token, TOKEN_EOF);
			break ;
		}
		process_char(token, cmd, c);
		while (token->next != NULL)
			token = token->next;
	}
}

t_token	*tokenize_cmd(char *line)
{
	t_token	*tokens;
	t_cmd	cmd;

	tokens = new_token(NULL, TOKEN_EOF);
	cmd = init_cmd(line);
	make_tokens(tokens, &cmd);
	return (tokens);
}
