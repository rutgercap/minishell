/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD:unit-tests/main.c
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
=======
/*                                                        ::::::::            */
/*   ft_free_char_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-der <dvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 08:23:11 by dvan-der      #+#    #+#                 */
/*   Updated: 2022/02/08 11:54:41 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	ft_free_char_array(char **split_str)
{
	int	i;

	i = 0;
	if (!split_str || !*split_str)
		return ;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
	return ;
>>>>>>> 07ab6cd8db233a7630aa7246c20985d02bd74785:srcs/utils/ft_free_char_array.c
}
