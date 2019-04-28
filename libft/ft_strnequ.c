/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:17:11 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:04:08 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		if (!*s1)
		{
			if (*s2)
				return (0);
			return (1);
		}
		while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
			i++;
		if (i == n || (!s1[i] && !s2[i]))
			return (1);
	}
	return (0);
}
