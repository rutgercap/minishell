#include <tokens.h>

static void word(char c, t_token *tokens, int finish_word)
{
	char	*new;
	
	if (!tokens || tokens->type != WORD || finish_word == 1)
		tokens = new_token(tokens, WORD);
	if (tokens->len + 1 % BUFF_SIZE == 1)
	{
		new = ft_calloc(tokens->len + BUFF_SIZE + 1, 1);
		ft_check_malloc(new, "word");
		ft_strcpy(new, tokens->text, tokens->len);
		free(tokens->text);
		tokens->text = new;
	}
	tokens->text[tokens->len] = c;
	tokens->len++;
}

static int	s_d_bracket(char c, int i, t_token *tokens, t_flag *flag)
{
	if (*flag == NORMAL)
	{
		if (c == '\'')
			*flag = S_BRACKET;
		else if (c == '\"')
			*flag = D_BRACKET;
	}
	else if (*flag == S_BRACKET)
	{
		if (c == '\'')
			*flag = NORMAL;
		else
			word(0, tokens, 1);
	}
	else if (*flag == D_BRACKET)
	{
		if (c == '\"')
			*flag = NORMAL;
		else
			word(0, tokens, 1);
	}
	return (i + 1);
}

static int	less_greater_than(char *line, int i, char c, t_token *tokens)
{
	if (line[i + 1] == c)
	{
		if (c == '<')
			tokens = new_token(tokens, INPUT_D);
		else
			tokens = new_token(tokens, OUTPUT_D);
		return (i + 2);
	}
	else
	{
		if (c == '<')
			tokens = new_token(tokens, INPUT_S);
		else
			tokens = new_token(tokens, OUTPUT_S);
		return (i + 1);
	}

}

static int	space(t_token *tokens, int i, t_flag *flag)
{
	if (*flag == NORMAL)
		word(0, tokens, 1);
	else
		word(' ', tokens, 0);
	return (i + 1);
}

int	check_char(char *line, int i, t_token *tokens, t_flag *flag)
{
	if (*flag == NORMAL)
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (s_d_bracket(line[i], i, tokens, flag)); 
		else if (line[i] == '<' || line[i] == '>')
			return (less_greater_than(line, i, line[i], tokens));
		else if (line[i] == '|')
		{
			tokens = new_token(tokens, PIPE);
			return (i + 1);
		}
	}
	if (*flag == S_BRACKET || *flag == D_BRACKET)
	{
		if (line[i] == '\'' || line[i] == '\"')
			return(s_d_bracket(line[i], i, tokens, flag));
	}
	if (ft_isspace(line[i]))
		return (space(tokens, i, flag));
	word(line[i], tokens, 0);
	return (i + 1);
}
