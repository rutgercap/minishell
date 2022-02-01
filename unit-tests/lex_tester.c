/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:15 by rcappend          #+#    #+#             */
/*   Updated: 2022/02/01 16:04:04 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "tokens.h"

void	lex_help_tester(char *line)
{
	t_token	*tokens;

	tokens = tokenizer(line);
	print_tokens(tokens);
}