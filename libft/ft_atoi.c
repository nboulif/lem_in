/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 01:09:24 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/16 00:43:50 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	resultat;
	int		signe;

	signe = 1;
	i = 0;
	resultat = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' ||
			str[i] == '\f')
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1] > 47 && str[i + 1] < 58)
		signe = (str[i] == '+') ? 1 : -1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return ((signe < 0) ? 0 : -1);
		i++;
	}
	return (signe * resultat);
}
