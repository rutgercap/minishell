/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 11:56:29 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/24 15:23:00 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token \'", STDERR_FILENO);
	ft_putstr_fd(token->text, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "init_cmd", NULL);
	}
	return (new);
}

static int	parse_oput_red(t_red *red, t_token *token)
{	
	token = token->next;
	if (token->type == OPUT_BRACK)
	{
		red->type = RED_OPUT_A;
		token = token->next;
	}
	else if (token->type == IPUT_BRACK)
		return (EXIT_FAILURE);
	else
		red->type = RED_OPUT;
	if (token->type != WORD || token->type != STRING || 
		token->type != PURE_STRING)
		return (EXIT_FAILURE);
	red->delim = token->text;
	return (EXIT_SUCCESS);
}

static int	parse_input_red(t_red *red, t_token *token)
{
	token = token->next;
	if (token->type == IPUT_BRACK)
	{
		red->type = HERE_DOC;
		token = token->next;
	}
	else if (token->type == OPUT_BRACK)
		return (EXIT_FAILURE);
	else
		red->type = RED_IPUT;
	if (token->type != WORD || token->type != STRING || 
		token->type != PURE_STRING)
		return (EXIT_FAILURE);
	red->delim = token->text;
	return (token);
}

static int	parse_brackets(t_cmd *cmd, t_token *token)
{
	if (token->type == OPUT_BRACK)
		return (parse_oput_red(&cmd->output, token));
	else
		return (parse_input_red(&cmd->input, token));
}

static int	parse_special_characters(t_cmd *cmd_list, t_token *tokens)
{
	t_token	*next;
	
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
		{
			cmd_list->next = new_cmd();
			cmd_list = cmd_list->next;
		}
		if (tokens->type == OPUT_BRACK || tokens->type == IPUT_BRACK)
		{
			if (parse_brackets(cmd_list, tokens))
				syntax_error(tokens);
		}
		tokens = next;
	}
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	
	cmd_list = new_cmd();
	
	// parse special characters
	// get command
	return (cmd_list);
}
