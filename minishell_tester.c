/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 06:04:49 by rcappend          #+#    #+#             */
/*   Updated: 2022/02/09 09:20:18 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static void	init_test(char *line)
{
	
}

trial_1()
{
	
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	UNITY_BEGIN();
	RUN_TEST(trial_1);
	return (UNITY_END());
}