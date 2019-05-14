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

void delete_this_edge(t_node *node, t_edge *edge)
{
	int				x;

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
					delete_this_edge(node->edge[0]->node1, node->edge[0]);
				else
					delete_this_edge(node->edge[0]->node2, node->edge[0]);
			}
			return ;
		}
}

void delete_dead_end()
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
									link->node->edge[0]);
				else
					delete_this_edge(link->node->edge[0]->node2,
									link->node->edge[0]);
			}
			link = link->next;
 		}
 	}
}

int create_tab_edge_in_node()
{
	int			i;
	t_node_link	*link;

	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (!(link->node->edge = malloc(link->node->nb_edge_o * sizeof(t_edge*))))
				return (0);
			link = link->next;
		}
	}
	return (1);
}

int rec_init_lst_edge_ord()
{
	t_queue queue;
	t_node *node;
	t_edge *edge;

	int j;
	int k;

	
	obj->lst_edge_ord = (t_edge**)malloc(sizeof(t_edge*) * obj->nb_edge);

	if (!(queue.node = ft_memalloc(sizeof(t_node*) * obj->nb_node)))
			return (0);

	ft_memset(obj->lst_edge_ord, 0, obj->nb_edge);
	ft_memset(queue.node, 0, obj->nb_node);

	queue.node[0] = obj->start_node;
	obj->start_node->deja_vu_in_way = 1;

	k = 0;
	queue.size_queue = 0;
	queue.index = -1;
	while(++queue.index <= queue.size_queue)
	{
		// printf("node %s \n", queue.node[queue.index]->name);

		j = -1;
		while(++j < queue.node[queue.index]->nb_edge_f)
		{	
			edge = queue.node[queue.index]->edge[j];

			if (queue.node[queue.index]->id == edge->node1->id)
				node = edge->node2;
			else
				node = edge->node1;
			

			if (!node->deja_vu_in_way)
			{
				node->deja_vu_in_way = 1;
				queue.node[++queue.size_queue] = node;
			}

			if (!edge->deja_vu_in_way)
			{
				edge->deja_vu_in_way = 1;
				obj->lst_edge_ord[k++] = edge;
			}


		}
	}
	obj->nb_edge_f = k;
	

	// exit(0);
	return (1);
}

int link_node_and_edge()
{
	int			i;
	t_node		*node1;
	t_node		*node2;

	i = -1;
	if (!create_tab_edge_in_node())
		return (0);
	while (++i < obj->nb_edge)
	{
		node1 = obj->lst_edge[i].node1;
		node2 = obj->lst_edge[i].node2;
		if (!is_in_tab_edge(node1->edge, obj->lst_edge + i, node1->nb_edge_f))
		{
			node1->edge[node1->nb_edge_f++] = obj->lst_edge + i;
			node2->edge[node2->nb_edge_f++] = obj->lst_edge + i;
		}
	}

	return (1);
}

int init_resolv()
{	
	if (!link_node_and_edge())
		return (0);
	delete_dead_end();
	rec_init_lst_edge_ord();
	return (1);
}