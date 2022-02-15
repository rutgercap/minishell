/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/14 10:39:10 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*new_cmd(bool pipe)
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
	if (pipe)
		new->input = new_redirect(R_PIPE);
	return (new);
}

static void	free_exec(t_exec *exec)
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
		return ;
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
		return (NULL);
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
