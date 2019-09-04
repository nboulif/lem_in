/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 04:02:54 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/04 20:27:44 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_node_and_edge(char *str, int size)
{
	write(1, str, size - 1);
	if (str[size - 2] != '\n')
		ft_putchar('\n');
	free(str);
	ft_putchar('\n');
}
