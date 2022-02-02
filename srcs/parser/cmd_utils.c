/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/02 11:43:30 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "new_cmd", NULL);
	}
	new->exec = ft_calloc(1, sizeof(t_exec));
	if (!new->exec)
	{
		errno = ENOMEM;
		exit_error(errno, "new_cmd", NULL);
	}
	return (new);
}

void	append_argument(t_exec *exec, t_token *token)
{
	if (!exec->arguments)
	{
		exec->arguments = ft_calloc(1, sizeof(char *));
		if (!exec->arguments)
		{
			errno = ENOMEM;
			exit_error(errno, "append argument", NULL);
		}
	}
	exec->arguments[exec->len] = ft_strdup(token->text);
	if (!exec->arguments[exec->len])
	{
		errno = ENOMEM;
		exit_error(errno, "append argument", NULL);
	}
	if (exec->len == 0)
		exec->command = exec->arguments[0];
	exec->len++;
}

void	free_exec(t_exec *exec)
{
	while (exec->len > 0)
	{
		exec->len--;
		free(exec->arguments[exec->len]);
	}
	free(exec->arguments);
	free(exec);
}

void	free_cmd(t_cmd **ref)
{
	t_cmd	*cmd;
	
	if (!ref || !*ref)
	{
		errno = ENODATA;
		exit_error(errno, "free_cmd", NULL);
	}
	cmd = *ref;
	free_exec(cmd->exec);
	free_redirects(cmd->input);
	free_redirects(cmd->output);
	free(cmd);
}

void	*free_cmd_list(t_cmd **ref)
{
	t_cmd	*i;
	t_cmd	*next;

	if (!ref || !*ref)
	{
		errno = ENODATA;
		exit_error(errno, "free_cmd_list", NULL);
	}
	i = *ref;
	while (i != NULL)
	{
		next = i->next;
		free_cmd(&i);
		i = next;
	}
	return (NULL);
}
