/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 11:56:29 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/01 08:39:11 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int	syntax_error(const t_type type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token \'", STDERR_FILENO);
	if (type == PIPE)
		ft_putchar_fd('|', STDERR_FILENO);
	else if (type == OUTPUT_S || type == OUTPUT_D)
		ft_putchar_fd('>', STDERR_FILENO);
	else if (type == INPUT_S || type == INPUT_D)
		ft_putchar_fd('<', STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	parse_words(t_cmd *cmd, t_token *tokens)
{	
	while (true)
	{
		if (tokens->type == PIPE || tokens->type == TOKEN_EOF)
		{
			if (cmd->exec || cmd->input || cmd->output)
				cmd = cmd->next;
			else
			{
				syntax_error(tokens->type);
				return (EXIT_FAILURE);
			}
		}
		else
			append_argument(cmd->exec, tokens);
		if (tokens->type == TOKEN_EOF)
			break;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

static int	parse_pipes(t_cmd **cmd_list, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;
	
	cmd = new_cmd();
	head = cmd;
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
		{
			cmd->output = new_redirect(RED_PIPE);
			cmd->next = new_cmd();
			cmd = cmd->next;
		}
		tokens = tokens->next;
	}
	*cmd_list = head;
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
	if (parse_words(cmd_list, tokens))
	{
		free_cmd_list(&cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
