/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_tester.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:10:47 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/14 14:22:13 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

void    system_call(char *cmd, int i)
{
	const char	*dest = "> results/diff/bash_";
	const char	*suffix = ".txt";
	char		*str_1;
	char		*str_2;

	str_1 = ft_strjoin(cmd, dest);
	str_2 = ft_strjoin(str_1, ft_itoa(i));
	free(str_1);
	str_1 = ft_strjoin(str_2, suffix);
	system(str_1);
	free(str_1);
	free(str_2);
}

void    setUp(void)
{
    
}

void    tearDown(void)
{
    
}



int main(void)
{
	
	while (true) {}
}