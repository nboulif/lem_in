/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:21:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:21:40 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define MIN(x,y) (x < y ? x : y)
#define SIX_GB 6442450944

void 		init_graph_bf(t_objectif *obj, int first_time)
{
	int i;
	int j;
	t_node_link *link;

	i = 0;
	while (i < obj->nb_node)
	{
		link = obj->lst_node_lk[i++];
		while (link)
		{
			j = -1;
			while (++j < link->node->nb_edge_f)
				link->node->edge[j]->deja_vu = 0;
			if (first_time)
			{
				link->node->D = __INT_MAX__;
				link->node->last_D = __INT_MAX__;
			}
			link->node->deja_vu = 0;
			ft_memset(link->node->fathers, 0, 1 * sizeof(t_father));
			ft_memset(link->node->father_node, 0, 1 * sizeof(t_node*));
			ft_memset(link->node->father_edge, 0, 1 * sizeof(t_edge*));
			link = link->next;
		}
	}
	if (first_time)
		obj->start_node->D = 0;
}

int 		init_way(t_objectif *obj, t_way *way, int mode)
{
	static t_node_link *n_link_allocation_zone = NULL;
	static t_edge_link *e_link_allocation_zone = NULL;
	static unsigned long index = 0;
	static unsigned long size = 0;

	if (mode == 0)
	{
		free(e_link_allocation_zone);
		free(n_link_allocation_zone);
		return (1);
	}
	else if (!n_link_allocation_zone || !e_link_allocation_zone)
	{
		size = (unsigned long)obj->nb_node * (unsigned long)obj->nb_node * (unsigned long)(obj->max_way * 2);
		printf("first_alloc == |%lu|, nb_node^2 |%lu|\n", size, (unsigned long)obj->nb_node * (unsigned long)obj->nb_node);
		if (!n_link_allocation_zone &&
			!(n_link_allocation_zone = (t_node_link*)malloc(MIN(sizeof(t_node_link) * size, SIX_GB))))
				return (0);
		if (!(e_link_allocation_zone) &&
			!(e_link_allocation_zone = (t_edge_link*)malloc(MIN(sizeof(t_edge_link) * size, SIX_GB))))
				return (0);
		size = MIN(MIN(SIX_GB, size * sizeof(t_edge_link)), size * sizeof(t_node_link));
	}
	index += obj->nb_node * obj->nb_node;
	printf("alloc index == |%lu|\n", index);
	if (index >= size)
		return (0);
	way->nodes_lk = &n_link_allocation_zone[index];
	way->edges_lk = &e_link_allocation_zone[index];
	//if (!(way->nodes_lk = (t_node_link*)malloc(sizeof(t_node_link) * (obj->nb_node * obj->nb_node))) ||
	//	!(way->edges_lk = (t_edge_link*)malloc(sizeof(t_edge_link) * (obj->nb_node * obj->nb_node))))
	//	return (0);
	return (1);
}

int			init_solution(t_objectif *obj, t_solution  *sol, t_queue *queue)
{
	if (!(sol->way = malloc(sizeof(t_way) * sol->nb_way)) ||
		!(queue->node = ft_memalloc(sizeof(t_node*) * obj->nb_node)) ||
		!init_way(obj, &sol->way[sol->nb_way - 1], 1))
		return (0);
	return (1);
}

int			clone_way(t_objectif *obj, t_solution *sol, t_solution *cur)
{
	int		i;
	t_node_link	*nodes_lk;
	t_edge_link	*edges_lk;

	ft_memcpy(sol->way, cur->way, (sol->nb_way-1) * sizeof(t_way));
	i = -1;
	while (++i < cur->nb_way)
	{
		if (!(nodes_lk = (t_node_link*)malloc(sizeof(t_node_link) * (obj->nb_node))) ||
			!(edges_lk = (t_edge_link*)malloc(sizeof(t_edge_link) * (obj->nb_node))))
			return (0);
		ft_memcpy(nodes_lk, cur->way[i].nodes_lk, (obj->nb_node) * sizeof(t_node_link*));
		ft_memcpy(edges_lk, cur->way[i].edges_lk, (obj->nb_node) * sizeof(t_edge_link*));
		sol->way[i].edges_lk = edges_lk;
		sol->way[i].nodes_lk = nodes_lk;
	}
	return (1);
}