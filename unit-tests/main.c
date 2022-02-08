/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:15 by rcappend          #+#    #+#             */
/*   Updated: 2022/02/01 16:03:56 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "tokens.h"

// void    setUp(void) {

// }

// void    tearDown(void) {
    
// }

void	lextester1(void)
{
	t_token	*tokens;

	tokens = lex_help_tester("echo hallo | cat")
	
}

int main(void)
{
    UNITY_BEGIN();
	RUN_TEST(lextester1);
    printf("no error!\n");
    return UNITY_END();
}
