/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_words.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 08:47:01 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/05 09:27:14 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	append_to_arguments(t_exec *exec, char	*new_arg)
{
	char	**args;
	int		i;

	args = ft_calloc(exec->len + 2, sizeof(char *));
	if (!args)
	{
		errno = ENOMEM;
		exit_error(errno, "append_to_arguments", NULL);
	}
	i = 0;
	while (i < exec->len)
	{
		args[i] = exec->arguments[i];
		i++;
	}
	args[i] = new_arg;
	exec->len++;
	free(exec->arguments);
	exec->arguments = args;
	exec->command = exec->arguments[0];
}

void	add_argument(t_exec *exec, t_token *token)
{
	char	*new;
	
	if (!exec->arguments)
	{
		exec->arguments = ft_calloc(1, sizeof(char *));
		if (!exec->arguments)
		{
			errno = ENOMEM;
			exit_error(errno, "append argument", NULL);
		}
	}
	new = ft_strdup(token->text);
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "append argument", NULL);
	}
	append_to_arguments(exec, new);
}

int	parse_words(t_cmd *cmd, t_token *tokens)
{	
	while (true)
	{
		if (tokens->type == TOKEN_EOF)
		{
			if (tokens->prev->type != WORD)
				return (syntax_error(tokens->prev->type));
			break;
		}
		if (tokens->type == PIPE)
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
			add_argument(cmd->exec, tokens);
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}