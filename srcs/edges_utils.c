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


t_node 		*get_right_node_in_edge(t_edge *edge, t_node *node, int verif)
{
	if (verif && edge->deja_vu)
		return (NULL);
	if (node == edge->node1)
	{
		if (verif && !(edge->direction & UNIDIR2))
			return (NULL);
		return (edge->node2);
	}
	else if (node == edge->node2)
	{
		if (verif && !(edge->direction & UNIDIR1))
			return (NULL);
		return (edge->node1);
	}
	return (NULL);
}