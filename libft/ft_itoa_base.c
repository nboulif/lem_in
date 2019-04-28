/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 05:33:41 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 10:58:31 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_recurs_baseto(long nbr, char *convert, char *base, int index)
{
	long	nb_digit;

	nb_digit = 0;
	while (base[nb_digit])
		nb_digit++;
	convert[index] = base[nbr % nb_digit];
	if (nbr >= nb_digit)
		return (ft_recurs_baseto(nbr / nb_digit, convert, base, index - 1));
	return (convert);
}

static int	ft_size_malloc(long nbr, long base, int base_clone, int count)
{
	if (nbr < 0)
		return (ft_size_malloc(-nbr, base * base, base_clone, count + 1));
	if (nbr > base)
		return (ft_size_malloc(nbr, base * base_clone, base_clone, count + 1));
	else if (nbr == base)
		return (count + 1);
	return (count);
}

char		*ft_itoa_base(int nb, char *base)
{
	char	*result;
	size_t	b_size;
	char	signe;
	long	nbr;

	nbr = nb;
	signe = 0;
	if (nbr < 0)
	{
		signe = -1;
		nbr = -nbr;
	}
	b_size = ft_strlen(base);
	if (!(result = (char*)malloc(sizeof(char) *
			(b_size = (ft_size_malloc(nbr, b_size, b_size, 1) + 1 - signe)))))
		return (NULL);
	result[b_size - 1] = '\0';
	if (signe == -1)
		result[0] = '-';
	return (ft_recurs_baseto(nbr, result, base, b_size - 2));
}
/*
**#include <stdio.h>
**
**int main()
**{
**	printf ("%s\n", ft_itoa_base(-170, "0123456789ABCDEF"));
**	return (0);
**}
*/
