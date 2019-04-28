/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 00:16:24 by rhunders          #+#    #+#             */
/*   Updated: 2019/02/17 00:16:28 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_indexof(char const *str, char to_find)
{
	int		count;

	count = 0;
	if (!str)
		return (-1);
	while (str[count] && str[count] != to_find)
		count++;
	return (str[count] || !to_find ? count : -1);
}
