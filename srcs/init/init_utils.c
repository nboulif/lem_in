/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 23:13:20 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:44:11 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	zap_line(char *str, int *i)
{
	while (str[*i])
	{
		*i += 1;
		if (str[*i] == '\n')
		{
			*i += 1;
			return ;
		}
	}
}

void	zap_comm(char *str, int *i)
{
	while (str[*i] == '#')
		zap_line(str, i);
}

int		number_check(char *str)
{
	long	number;

	number = ft_atol(str);
	return (number <= INT_MAX && number >= INT_MIN);
}

int		check_coord(char *str)
{
	int i;

	if (!ft_isdigit(str[0]))
	{
		if (str[0] != '-' && str[0] != '+')
			return (0);
		i = 1;
	}
	else
		i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (!(str[i] != ' ' || !ft_isdigit(str[i + 1]) ||
		!number_check(str) || !number_check(&str[i + 1])));
}
