/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 11:56:29 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/25 14:15:38 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token \'", STDERR_FILENO);
	ft_putstr_fd(token->text, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	parse_pipes(t_cmd **cmd_list, t_token *tokens)
{
	t_cmd	*cmd;
	
	cmd = new_cmd();
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == ERROR)
		{
			*cmd_list = cmd;
			return (syntax_error(tokens));	
		}
		else if (tokens->type == PIPE)
		{
			cmd->output = new_redirect(RED_PIPE);
			cmd->next = new_cmd();
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	*cmd_list = cmd;
	return (EXIT_SUCCESS);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	
	if (tokens->type == TOKEN_EOF)
		return (NULL);
	cmd_list = NULL;
	if (parse_pipes(&cmd_list, tokens))
	{
		free_cmd_list(&cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
