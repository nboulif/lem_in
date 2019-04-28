/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_resolv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:17:16 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/26 17:17:16 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void delete_this_tube(t_node *node, t_tube *tube, t_objectif *obj)
{
	int				x;

	x = -1;
	while (++x < node->nb_tube_f)
		if (node->tube[x] == tube)
		{
			node->tube[x] = node->tube[--node->nb_tube_f];
			if (node->nb_tube_f == 1 &&
				node != obj->start_node &&
				node != obj->end_node)
			{
				if (node == node->tube[0]->node2)
					delete_this_tube(node->tube[0]->node1, node->tube[0], obj);
				else
					delete_this_tube(node->tube[0]->node2, node->tube[0], obj);
			}
			return ;
		}
}

void delete_dead_end(t_objectif *obj)
{
 	int			i;
 	t_node_link	*link;

 	i = -1;
 	while (++i < obj->nb_node)
 	{
 		link = obj->lst_node_lk[i];
 		while (link)
 		{
			if (link->node->nb_tube_f == 1 &&
				link->node != obj->start_node &&
				link->node != obj->end_node)
			{
				if (link->node == link->node->tube[0]->node2)
					delete_this_tube(link->node->tube[0]->node1,
									link->node->tube[0], obj);
				else
					delete_this_tube(link->node->tube[0]->node2,
									link->node->tube[0], obj);
			}
			link = link->next;
 		}
 	}
}

int create_tab_tube_in_node(t_objectif *obj)
{
	int			i;
	t_node_link	*link;

	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (!(link->node->tube = malloc(link->node->nb_tube_o * sizeof(t_tube*))))
				return (0);
			link = link->next;
		}
	}
	return (1);
}

int link_node_and_tube(t_objectif *obj)
{
	int			i;
	t_node		*node1;
	t_node		*node2;

	i = -1;
	if (!create_tab_tube_in_node(obj))
		return (0);
	while (++i < obj->nb_tube)
	{
		node1 = obj->lst_tube[i].node1;
		node2 = obj->lst_tube[i].node2;
		if (!is_in_tab_tube(node1->tube, obj->lst_tube + i, node1->nb_tube_f))
		{
			node1->tube[node1->nb_tube_f++] = obj->lst_tube + i;
			node2->tube[node2->nb_tube_f++] = obj->lst_tube + i;
		}
	}
	return (1);
}

int init_resolv(t_objectif *obj)
{	
	if (!link_node_and_tube(obj))
		return (0);
	delete_dead_end(obj);
	return (1);
}