/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:19:21 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/26 11:02:50 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	parse_output_red(char **delim, t_red_type *type, t_token *token)
{
	int		steps;

	token = token->next;
	steps = 1;
	if (token->type == OPUT_BRACK)
	{
		*type = RED_OPUT_A;
		token = token->next;
		steps++;
	}
	else if (token->type == IPUT_BRACK)
		return (SYNTAX_ERROR);
	else
		*type = RED_OPUT;
	if (token->type != WORD || token->type != STRING || 
		token->type != PURE_STRING)
		return (SYNTAX_ERROR);
	*delim = token->text;
	token->text = NULL;
	return (steps);
}

static int	parse_input_red(char **delim, t_red_type *type, t_token *token)
{
	int		steps;

	token = token->next;
	steps = 1;
	if (token->type == IPUT_BRACK)
	{
		*type = HERE_DOC;
		token = token->next;
		steps++;
	}
	else if (token->type == OPUT_BRACK)
		return (SYNTAX_ERROR);
	else
		*type = RED_IPUT;
	if (token->type != WORD && token->type != STRING && 
		token->type != PURE_STRING)
		return (SYNTAX_ERROR);
	*delim = token->text;
	token->text = NULL;
	return (steps);
}

int	add_redirect(t_red **dest, t_token *token, t_type type)
{
	t_red	*i;

	i = *dest;	
	if (i)
	{
		while (i->next)
			i = i->next;
		i->next = new_redirect(UNDEFINED);
		i = i->next;
	}
	else
	{
		*dest = new_redirect(UNDEFINED);
		i = *dest;
	}
	if (type == IPUT_BRACK)
		return (parse_input_red(&i->delim, &i->type, token));
	else
		return (parse_output_red(&i->delim, &i->type, token));
}

t_token	*step_tokens(t_token *tokens, int steps)
{
	while (steps > 0)
	{
		tokens = delete_token(&tokens);
		steps--;
	}
	return (tokens);
}

int	parse_redirects(t_cmd *cmds, t_token *tokens)
{
	int		steps;
	
	while (tokens->type != TOKEN_EOF)
	{
		steps = 0;
		if (tokens->type == PIPE)
			cmds = cmds->next;
		else if (tokens->type == IPUT_BRACK)
			steps = add_redirect(&cmds->input, tokens, tokens->type);
		else if (tokens->type == OPUT_BRACK)
			steps = add_redirect(&cmds->output, tokens, tokens->type);
		if (steps < 0)
			return (syntax_error(tokens));
		else if (steps)
			step_tokens(tokens, steps);
		else
			tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
