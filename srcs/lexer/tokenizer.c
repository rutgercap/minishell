#include <tokens.h>

static int	is_special_char(char c)
{
	return ((c == '|' || c == '>' || c == '<' || 
		c == '\\' || c == '\"' || c == '\''));
}

static int	is_delimiter(char c)
{
	return ((c == CMD_EOF || c == ';' || c == '&') 
		|| ft_isspace(c) || is_special_char(c));
}

static void	add_word(t_token *token, t_cmd *cmd)
{
	char	c;

	token->type = WORD;
	c = 0;
	while (true)
	{
		c = next_char(cmd);
		if (is_delimiter(c))
			return ;
		append_to_text(token, c);
	}
}

static void	make_tokens(t_token *token, t_cmd *cmd)
{
	t_token	*i;
	char	c;

	i = token;
	c = 0;
	while (true)
	{
		skip_white_spaces(cmd);
		c = next_char(cmd);
		if (c == CMD_EOF)
			break ;
		if (is_special_char(c))
			special_character(token, cmd);
		else
		{
			token->type = WORD;
			append_to_text(token, c);
		}
	}
}

t_token	*tokenize_cmd(char *line)
{
	t_token	*tokens_ref;
	t_cmd	cmd;

	tokens_ref = new_token(NULL, TOKEN_EOF);
	cmd = init_cmd(line);
	make_tokens(tokens_ref, &cmd);
	return (tokens_ref);
}
