/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:46:08 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:46:09 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int is_same_tube(t_tube tube1, t_tube tube2)
{
	return ((tube1.node1 == tube2.node1 || tube1.node1 == tube2.node2) &&
		(tube1.node2 == tube2.node1 || tube1.node2 == tube2.node2));
}

int	is_in_tab_tube(t_tube **tab, t_tube *to_find, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (is_same_tube(*(tab[i]), *to_find))
			return (1);
	return (0);
}
