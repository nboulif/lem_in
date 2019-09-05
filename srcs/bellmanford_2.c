/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellmanford_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 21:11:52 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 17:47:05 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_dist_deja_vu_lst(t_objectif *obj)
{
	int	i;

	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dists[obj->lst_node[i]->id + obj->nb_node] = __INT_MAX__;
		obj->dists[obj->lst_node[i]->id] = __INT_MAX__;
	}
	obj->dists[obj->start_node->id] = 0;
	obj->dists[obj->start_node->id + obj->nb_node] = 0;
	obj->dists[obj->end_node->id] = __INT_MAX__;
	obj->dists[obj->end_node->id + obj->nb_node] = __INT_MAX__;
	return (1);
}

void	init_right_bf_utils(t_bf_utils *bf, t_edge *e, int mode)
{
	if (mode == 1)
	{
		bf->u = e->node1;
		bf->v = e->node2;
		bf->w = e->w1;
	}
	else
	{
		bf->u = e->node2;
		bf->v = e->node1;
		bf->w = e->w2;
	}
}
