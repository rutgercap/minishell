/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 11:15:15 by rcappend      #+#    #+#                 */
/*   Updated: 2022/02/01 17:04:15 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static int  test_parser(void)
{
    UNITY_BEGIN();
    return UNITY_END();
}

int main(void)
{
    test_lexer();
    test_parser();
    return (0);
}
