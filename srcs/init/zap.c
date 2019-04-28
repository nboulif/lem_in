/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 23:13:20 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/26 23:56:05 by nboulif          ###   ########.fr       */
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
