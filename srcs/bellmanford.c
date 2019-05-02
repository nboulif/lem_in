/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellmanford.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 21:11:52 by nboulif           #+#    #+#             */
/*   Updated: 2019/05/02 21:11:54 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void check_bellman_ford(t_objectif *obj, t_solution *sol, int **dist, t_edge *e, int mode)
{
	t_node *u;
	t_node *v;
	int 	w;
	int 	dir;
	
	if (mode == 1)
	{
		u = e->node1;
		v = e->node2;
		w = e->w1;
		dir = UNIDIR1;
	}
	else
	{
		u = e->node2;
		v = e->node1;
		w = e->w2;
		dir = UNIDIR2;
	}
	
	if (
		u != v && u != obj->end_node &&
		(e->direction == BIDIR || e->direction == dir) &&
		// (
		// 	!u->deja_vu || !u->father_node[sol->nb_way] || 
		// 	( 
		// 		( 
		// 			(!v->deja_vu && u->father_node[sol->nb_way]->deja_vu) 
		// 			|| 
		// 			(v->deja_vu && !u->father_node[sol->nb_way]->deja_vu) 
		// 		)
		// 	)
		// ) &&
		(*dist)[u->id] != __INT_MAX__ && (*dist)[u->id] + w < (*dist)[v->id]
		) 
	{
		obj->dist_up = 1;
		(*dist)[v->id] = (*dist)[u->id] + w;
		v->father_node[sol->nb_way] = u;
		v->father_edge[sol->nb_way] = e;
	}
}

void apply_algo_bellman_ford(t_objectif *obj, t_solution *sol, int **dist)
{
	int i;
	int j;

	t_edge *e;
	
	obj->dist_up = 0;

	i = 0;
	while (++i < obj->nb_node)
	{
		
		j = obj->nb_edge_f;
		// j = -1;
		while (--j >= 0)
		// while (++j < obj->nb_edge_f)
		{
			e = obj->lst_edge_ord[j];
			check_bellman_ford(obj, sol, dist, e, 1);
			check_bellman_ford(obj, sol, dist, e, 2);
		}
		if (!obj->dist_up)
			break;
	}
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}
