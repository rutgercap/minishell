/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:19:21 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/05 11:50:05 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_token	*delete_red_tokens(t_token *token)
{
	t_token	*next;
	t_token	*i;

	next = token->next->next;
	i = token->next;
	delete_token(&token);
	delete_token(&i);
	return (next);
}

static int	add_redirect(t_red **dest, t_token *token)
{
	t_red	*new;

	new = new_redirect(token->type - 2);
	if (!new)
		ft_check_malloc(new, "add_redirect");
	token = token->next;
	if (token->type != WORD)
	{
		syntax_error(token->type);
		return (EXIT_FAILURE);
	}
	new->delim = ft_strdup(token->text);
	if (!new->delim)
		ft_check_malloc(new->delim, "add_redirect");
	*dest = new;
	return (EXIT_SUCCESS);
}

static int	append_redirect(t_cmd *cmd, t_token *token)
{
	t_red	*i;

	if ((token->type == INPUT_S || token->type == INPUT_D) &&
		!cmd->input)
		return (add_redirect(&cmd->input, token));
	else if (!cmd->output)
		return (add_redirect(&cmd->output, token));
	if (token->type == INPUT_S || token->type == INPUT_D)
		i = cmd->input;
	else
		i = cmd->output;
	while (i->next)
		i = i->next;
	return (add_redirect(&i->next, token));
}

int	parse_redirects(t_cmd *cmds, t_token *tokens)
{
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
		{
			cmds = cmds->next;
			tokens = tokens->next;
		}
		else if (tokens->type >= INPUT_S && tokens->type <= OUTPUT_D)
		{
			if (append_redirect(cmds, tokens))
				return (EXIT_FAILURE);
			tokens = delete_red_tokens(tokens);
		}
		else
			tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
