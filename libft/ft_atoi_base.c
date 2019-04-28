/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 03:58:15 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 08:16:11 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_recurs_base(char *str, char *base, int acc, int index)
{
	int i;
	int i2;
	int i3;

	i3 = 0;
	i2 = 0;
	i = 0;
	while (base[i3])
		i3++;
	while (str[index] && str[index] != base[i] && base[i])
		i++;
	if (str[index] && base[i])
		return (ft_recurs_base(str, base, acc * i3 + i, index + 1));
	else if (i >= i3 && str[index] != '-' && str[index] != '+')
		return (0);
	else
		return (acc);
}

int			ft_atoi_base(char *str, char *base)
{
	int i;
	int resultat;
	int signe;

	signe = 1;
	i = 0;
	resultat = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	return (signe * ft_recurs_base(str + i, base, 0, 0));
}
/*
**int main()
**{
**	printf("%d", ft_atoi_base("yenop","poney"));
**	return (0);
**}
*/
