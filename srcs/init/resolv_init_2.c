/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_init_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:17:16 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:49:00 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_this_edge(t_node *node, t_edge *edge, t_objectif *obj)
{
	int x;

	x = -1;
	while (++x < node->nb_edge_f)
		if (node->edge[x] == edge)
		{
			node->edge[x] = node->edge[--node->nb_edge_f];
			if (node->nb_edge_f == 1 &&
				node != obj->start_node &&
				node != obj->end_node)
			{
				if (node == node->edge[0]->node2)
					delete_this_edge(node->edge[0]->node1, node->edge[0], obj);
				else
					delete_this_edge(node->edge[0]->node2, node->edge[0], obj);
			}
			return ;
		}
}

void	delete_dead_end(t_objectif *obj)
{
	int			i;
	t_node_link	*link;

	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (link->node->nb_edge_f == 1 &&
				link->node != obj->start_node &&
				link->node != obj->end_node)
			{
				if (link->node == link->node->edge[0]->node2)
					delete_this_edge(link->node->edge[0]->node1,
									link->node->edge[0], obj);
				else
					delete_this_edge(link->node->edge[0]->node2,
									link->node->edge[0], obj);
			}
			link = link->next;
		}
	}
}
