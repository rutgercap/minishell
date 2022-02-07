/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:19:21 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/07 13:30:49 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_token	*delete_red_tokens(t_token **head, t_token *token)
{
	t_token	*next;
	t_token	*i;

	next = token->next->next;
	if (token->prev == NULL)
		*head = next;
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
	new->file_name = ft_strdup(token->text);
	if (!new->file_name)
		ft_check_malloc(new->file_name, "add_redirect");
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

int	parse_redirects(t_cmd *cmds, t_token **tokens)
{
	t_token	*i;
	
	i = *tokens;
	while (i->type != TOKEN_EOF)
	{
		if (i->type == PIPE)
		{
			cmds = cmds->next;
			i = i->next;
		}
		else if (i->type >= INPUT_S && i->type <= OUTPUT_D)
		{
			if (append_redirect(cmds, i))
				return (EXIT_FAILURE);
			i = delete_red_tokens(tokens, i);
		}
		else
			i = i->next;
	}
	return (EXIT_SUCCESS);
}
