/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-der <dvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:23:11 by dvan-der          #+#    #+#             */
/*   Updated: 2022/02/04 12:21:23 by dvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	ft_free_char_array(char **split_str)
{
	int	i;

	i = 0;
	if (!split_str)
		return ;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
	return ;
}
