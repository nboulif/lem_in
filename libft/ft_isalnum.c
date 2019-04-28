/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:37:45 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/07 16:42:56 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*
**#include <stdio.h>
**#include <ctype.h>
**
**int main()
**{
**	int c;
**	c = 'a';
**	c = c << 4;
**	c += '8';
**	printf("%d\n", ft_isalnum(c));
**	printf("%d\n", ft_isalnum('8'));
**	printf("%d\n", ft_isalnum('*'));
**	printf("%d\n", isalnum(c));
**	printf("%d\n", isalnum('8'));
**	printf("%d\n", isalnum('*'));
**	return (0);
**}
*/
