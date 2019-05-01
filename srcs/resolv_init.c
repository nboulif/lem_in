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
			ft_memset(link->node->father_node, 0, 1 * sizeof(t_node*));
			ft_memset(link->node->father_edge, 0, 1 * sizeof(t_edge*));
			link = link->next;
		}
	}
	if (first_time)
		obj->start_node->D = 0;
}

int 		init_way(t_objectif *obj, t_way *way)
{
	if (!(way->node = malloc(sizeof(t_node*) * (obj->nb_node))) ||
		!(way->edge = malloc(sizeof(t_edge*) * (obj->nb_node))))
		return (0);
	return (1);
}

int			init_solution(t_objectif *obj, t_solution  *sol, t_queue *queue)
{
	if (!(sol->way = malloc(sizeof(t_way) * sol->nb_way)) ||
		!(queue->node = ft_memalloc(sizeof(t_node*) * obj->nb_node)) ||
		!init_way(obj, sol->way + sol->nb_way - 1))
		return (0);
	return (1);
}

int			clone_way(t_objectif *obj, t_solution *sol, t_solution *cur)
{
	int		i;
	t_node	**node;
	t_edge	**edge;

	ft_memcpy(sol->way, cur->way, (sol->nb_way-1) * sizeof(t_way));
	i = -1;
	while (++i < cur->nb_way)
	{
		if (!(node = malloc(sizeof(t_node*) * (obj->nb_node))) ||
		!(edge = malloc(sizeof(t_edge*) * (obj->nb_node))))
			return (0);
		ft_memcpy(edge, cur->way[i].edge, (obj->nb_node) * sizeof(t_edge*));
		ft_memcpy(node, cur->way[i].node, (obj->nb_node) * sizeof(t_node*));
		sol->way[i].edge = edge;
		sol->way[i].node = node;
	}
	return (1);
}