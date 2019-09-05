/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellmanford.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 21:11:52 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 17:47:09 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	bf_both_deja_vu(t_objectif *obj, t_bf_utils *bf, t_edge *e)
{
	if (e->deja_vu && obj->dists[bf->u->id] != __INT_MAX__ &&
		obj->dists[bf->u->id] + bf->w < obj->dists[bf->v->id + obj->nb_node])
	{
		obj->dist_up = 1;
		if (obj->dists[bf->v->id + obj->nb_node] == INT_MAX)
			obj->queue.node[obj->queue.size_queue++] = bf->v;
		obj->dists[bf->v->id + obj->nb_node] = obj->dists[bf->u->id] + bf->w;
		bf->v->fathers[obj->next_sol.nb_way].node_out = bf->u;
		bf->v->fathers[obj->next_sol.nb_way].edge_out = e;
		bf->v->father_mode = 0;
		if (obj->dists[bf->v->id + obj->nb_node] < obj->dists[bf->v->id]
			|| obj->dists[bf->v->id] == __INT_MAX__)
		{
			obj->dists[bf->v->id] = obj->dists[bf->v->id + obj->nb_node];
			bf->v->fathers[obj->next_sol.nb_way].node = bf->u;
			bf->v->fathers[obj->next_sol.nb_way].edge = e;
			bf->v->fathers[obj->next_sol.nb_way].mode = 0;
		}
	}
}

int		bf_other(t_objectif *obj, t_bf_utils *bf, t_edge *e)
{
	if (bf->u->deja_vu && !bf->v->deja_vu)
	{
		if (obj->dists[bf->u->id + obj->nb_node] == __INT_MAX__ ||
				obj->dists[bf->v->id] <= obj->dists[bf->u->id +
				obj->nb_node] + bf->w)
			return (1);
		if (obj->dists[bf->v->id] == INT_MAX)
			obj->queue.node[obj->queue.size_queue++] = bf->v;
		obj->dists[bf->v->id] = obj->dists[bf->u->id + obj->nb_node] + bf->w;
		bf->v->father_mode = 1;
	}
	else
	{
		if (obj->dists[bf->u->id] == __INT_MAX__ ||
			obj->dists[bf->u->id] + bf->w >= obj->dists[bf->v->id])
			return (1);
		if (obj->dists[bf->v->id] == INT_MAX)
			obj->queue.node[obj->queue.size_queue++] = bf->v;
		obj->dists[bf->v->id] = obj->dists[bf->u->id] + bf->w;
		bf->v->father_mode = 0;
	}
	obj->dist_up = 1;
	bf->v->fathers[obj->next_sol.nb_way].node = bf->u;
	bf->v->fathers[obj->next_sol.nb_way].edge = e;
	return (0);
}

void	check_bellman_ford(t_objectif *obj, t_edge *e, int mode)
{
	t_bf_utils	bf;

	init_right_bf_utils(&bf, e, mode);
	if (bf.u != bf.v && bf.u != obj->end_node
		&& bf.v != obj->start_node
		&& (!bf.u->deja_vu || bf.v->deja_vu ||
		(bf.u->fathers[obj->next_sol.nb_way].node_out)))
	{
		if (bf.u->deja_vu && bf.v->deja_vu)
			bf_both_deja_vu(obj, &bf, e);
		else if (bf_other(obj, &bf, e))
			return ;
	}
}

void	apply_algo_bellman_ford_part_two(t_objectif *obj, int o)
{
	int			j;
	t_edge		*e;

	j = -1;
	while (++j < obj->queue.node[o]->nb_edge_f)
	{
		e = obj->queue.node[o]->edge[j];
		if (e->direction == NODIR)
			continue ;
		if (obj->queue.node[o] == e->node1 && e->direction & UNIDIR1)
			check_bellman_ford(obj, e, 1);
		else if (obj->queue.node[o] == e->node2 && e->direction & UNIDIR2)
			check_bellman_ford(obj, e, 2);
	}
}

int		apply_algo_bellman_ford(t_objectif *obj)
{
	int			i;
	int			o;

	init_dist_deja_vu_lst(obj);
	obj->queue.size_queue = 1;
	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		o = -1;
		while (++o < obj->queue.size_queue)
			apply_algo_bellman_ford_part_two(obj, o);
		if (!obj->dist_up)
			break ;
	}
	obj->next_sol.way[obj->next_sol.nb_way].cost = obj->dists[obj->nb_node - 1];
	if (obj->dists[obj->nb_node - 1] == __INT_MAX__)
		return (0);
	return (1);
}
