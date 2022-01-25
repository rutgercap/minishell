/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:19:21 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/25 14:24:12 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	parse_output_red(t_red *red, t_token *token)
{
	int		steps;

	token = token->next;
	steps = 1;
	if (token->type == OPUT_BRACK)
	{
		red->type = RED_OPUT_A;
		token = token->next;
		steps++;
	}
	else if (token->type == IPUT_BRACK)
		return (SYNTAX_ERROR);
	else
		red->type = RED_OPUT;
	if (token->type != WORD || token->type != STRING || 
		token->type != PURE_STRING)
		return (SYNTAX_ERROR);
	red->delim = token->text;
	token->text = NULL;
	return (steps);
}

static int	parse_input_red(t_red *red, t_token *token)
{
	int		steps;

	token = token->next;
	steps = 1;
	if (token->type == IPUT_BRACK)
	{
		red->type = HERE_DOC;
		token = token->next;
		steps++;
	}
	else if (token->type == OPUT_BRACK)
		return (SYNTAX_ERROR);
	else
		red->type = RED_IPUT;
	if (token->type != WORD || token->type != STRING || 
		token->type != PURE_STRING)
		return (SYNTAX_ERROR);
	red->delim = token->text;
	token->text = NULL;
	return (steps);
}

int	add_redirect(t_red *dest, t_token *token, t_type type)
{
	if (dest)
	{
		while (dest->next)
			dest = dest->next;
		dest->next = new_redirect(UNDEFINED);
		dest = dest->next;
	}
	else
		dest = new_redirect(UNDEFINED);
	if (type == IPUT_BRACK)
		return (parse_input_red(dest, token));
	else
		return (parse_output_red(dest, token));
}

int	parse_redirects(t_cmd *cmds, t_token *tokens)
{
	int		steps;
	
	steps = 0;
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
			cmds = cmds->next;
		else if (tokens->type == IPUT_BRACK)
			steps = add_redirect(cmds->input, tokens, tokens->type);
		else if (tokens->type == OPUT_BRACK)
			steps = add_redirect(cmds->output, tokens, tokens->type);
		if (steps < 0)
			return (syntax_error(tokens));
		while (steps > 0 && tokens->next)
		{
			tokens = delete_token(&tokens);
			steps--;
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
