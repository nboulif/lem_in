/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:46:08 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:46:09 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int is_same_edge(t_edge edge1, t_edge edge2)
{
	return ((edge1.node1 == edge2.node1 || edge1.node1 == edge2.node2) &&
		(edge1.node2 == edge2.node1 || edge1.node2 == edge2.node2));
}

int	is_in_tab_edge(t_edge **tab, t_edge *to_find, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (is_same_edge(*(tab[i]), *to_find))
			return (1);
	return (0);
}
