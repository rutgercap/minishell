/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 08:26:32 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/25 13:49:25 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	free_cmd(t_cmd **ref)
{
	t_cmd	*cmd;
	
	if (!ref || !*ref)
	{
		errno = ENODATA;
		exit_error(errno, "free_cmd", NULL);
	}
	cmd = *ref;
	free(cmd->command);
	free(cmd->arguments);
	free_redirects(cmd->input);
	free_redirects(cmd->output);
	free(cmd);
}

t_cmd	*new_cmd(void)
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

void	free_cmd_list(t_cmd **ref)
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
}
