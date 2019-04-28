/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 03:10:21 by rhunders          #+#    #+#             */
/*   Updated: 2019/02/17 00:21:40 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static long	ft_recurs_base10(char *str, char *base, long acc, int index)
{
	long	i;
	long	i3;

	i3 = 0;
	i = 0;
	if (str[index] == '-' && index == 0)
		return (ft_recurs_base10(str, base, acc, index + 1));
	while (base[i3])
		i3++;
	while (str[index] && str[index] != base[i] && base[i])
		i++;
	if (str[index] && base[i])
		return (ft_recurs_base10(str, base, (long)acc * i3 + i, index + 1));
	else if (i >= i3 && str[index] != '-' && str[index] != '+')
		return (0);
	else if (str[0] == '-')
		return ((long)-acc);
	return (acc);
}

static char	*ft_recurs_baseto(long nbr, char *convert, char *base, int index)
{
	long nb_digit;

	nb_digit = 0;
	while (base[nb_digit])
		nb_digit++;
	convert[index] = base[nbr % nb_digit];
	if (nbr >= nb_digit)
		return (ft_recurs_baseto(nbr / nb_digit, convert, base, index - 1));
	return (convert);
}

static int	ft_check_base(int nb_digit, char *base)
{
	int i;
	int i2;

	i2 = 0;
	if (nb_digit < 2)
		return (0);
	while (i2 < nb_digit - 1)
	{
		i = i2 + 1;
		while (base[i] != '\0')
		{
			if (base[i2] == base[i] || base[i] == '+' ||
					base[i] == '-' || base[0] == '-' ||
					base[0] == '+')
				return (0);
			i++;
		}
		i2++;
	}
	return (1);
}

static int	ft_size_malloc(long nbr, long base, int base_clone, int count)
{
	if (nbr < 0)
		return (ft_size_malloc(-nbr, base * base, base_clone, count + 1));
	if (nbr > base)
		return (ft_size_malloc(nbr, base * base_clone, base_clone, count + 1));
	else if (nbr == base)
		return (count + 1);
	else
		return (count);
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	nb;
	char	*conv;
	int		var[3];
	int		sign;

	var[1] = 0;
	var[2] = 0;
	while (*nbr == ' ' || *nbr == '\t' || *nbr == '\n' ||
			*nbr == '\r' || *nbr == '\v' || *nbr == '\f')
		nbr++;
	nb = ft_recurs_base10(nbr, base_from, 0, 0);
	sign = (nb < 0) ? -3 : -2;
	var[0] = (nb < 0) ? 1 : 0;
	while (base_to[var[2]])
		var[2] += 1;
	while (base_from[var[1]])
		var[1] += 1;
	var[0] += ft_size_malloc(nb, var[2], var[2], 1) + 1;
	conv = (char*)malloc(sizeof(char) * var[0]);
	conv[var[0] - 1] = '\0';
	nb = (sign == -3) ? -nb : nb;
	conv[0] = '-';
	if (ft_check_base(var[1], base_from) && ft_check_base(var[2], base_to))
		return (ft_recurs_baseto(nb, conv, base_to, var[0] - 2));
	return (0);
}
/*
**#include <stdio.h>
**int main(int argc, char *argv[])
**{
**	if (argc == 4)
**		printf("%s \n", ft_convert_base(argv[1], argv[2], argv[3]));
**	return (0);
**}
*/
