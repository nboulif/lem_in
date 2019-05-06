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

int 		init_dist_deja_vu_lst(t_objectif *obj)
{
	int i;
	int j;

	obj->dists[0] = 0;
	i = 1;
	while (i < obj->nb_node)
		obj->dists[i++] = __INT_MAX__;
	i = -1;
	while (i++ < obj->nb_node)
	{
		j = 0;
		while (j < obj->nb_node)
			obj->deja_vus[i][j++] = -1;
	}
	return (1);
}

void 		check_negative_cycle(t_objectif *obj)
{
	int i;
	int u;
	int v;

	i = -1;
	while (++i < obj->nb_edge)
    {
		u = obj->lst_edge[i].node1->id;
		v = obj->lst_edge[i].node2->id;
        if (obj->dists[u] != __INT_MAX__ && obj->dists[u] + obj->lst_edge[i].w1 < obj->dists[v])
            printf("Graph contains negative weight cycle\n"); 
    } 
	
}

void 		check_bellman_ford(t_objectif *obj, t_solution *sol, t_edge *e, int mode)
{
	t_node *u;
	t_node *v;
	int 	w;
	
	if (mode == 1)
	{
		u = e->node1;
		v = e->node2;
		w = e->w1;
	}
	else
	{
		u = e->node2;
		v = e->node1;
		w = e->w2;
	}

	if (
		u != v && u != obj->end_node && v != obj->start_node
		// && (
		// 	!u->deja_vu
		// 	|| (
		// 		u->fathers[sol->nb_way].node
		// 		// && (obj->deja_vus[u->id][u->fathers[sol->nb_way].node->id] =! -1)
		// 		&& (
		// 			(
		// 				v->deja_vu
		// 				&& u->fathers[sol->nb_way].node
		// 				&& (obj->deja_vus[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE
		// 				|| obj->deja_vus[u->id][u->fathers[sol->nb_way].node->id] == IN_MODE)

		// 			)
		// 			||
		// 			(
		// 				!v->deja_vu
		// 				&& u->fathers[sol->nb_way].node
		// 				&& u->fathers[sol->nb_way].node->deja_vu
		// 				&& obj->deja_vus[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE
		// 			)
		// 		)
		// 	)
		// )
		&& (!u->deja_vu || 
			// (
			// 	u->fathers[sol->nb_way].node &&
			// 	(*deja_vu)[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE
			// )
			(
				v->deja_vu 
				&& (
					e->deja_vu 
				)
			) 
			|| (
				!v->deja_vu 
				&& u->fathers[sol->nb_way].node
				&& (obj->deja_vus[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE)
			) 
		) 
		// && (!u->deja_vu || v->deja_vu || 
		// (u->fathers[sol->nb_way].node && u->fathers[sol->nb_way].node->deja_vu)) 
		&& obj->dists[u->id] != __INT_MAX__ && 
		(
			obj->dists[u->id] + w < obj->dists[v->id] 
			// || (obj->dists[u->id] + w == obj->dists[v->id])
			// || (obj->dists[u->id] + w == obj->dists[v->id] && e->deja_vu)
		)
		)
	{
		// printf("|%s|-|%s| : %d -> %d \n", u->name, v->name,
		// 	obj->dists[v->id],
		// 	obj->dists[u->id] + w
		// );
		
		obj->dist_up = 1;
		obj->dists[v->id] = obj->dists[u->id] + w ;

		v->fathers[sol->nb_way].node = u;
		v->fathers[sol->nb_way].edge = e;

		if (!u->deja_vu)
			v->fathers[sol->nb_way].mode = NO_MODE;
		else if (!v->deja_vu)
			v->fathers[sol->nb_way].mode = OUT_MODE;
		else
			v->fathers[sol->nb_way].mode = IN_MODE;
		if (obj->deja_vus[v->id][u->id] == -1)
		{
			if (!u->deja_vu && v->deja_vu)
				obj->deja_vus[v->id][u->id] = IN_MODE;
			else if (!u->deja_vu && !v->deja_vu)
				obj->deja_vus[v->id][u->id] = NO_MODE;
			else if (u->deja_vu && !v->deja_vu)
				obj->deja_vus[v->id][u->id] = NO_MODE;
			else if (u->deja_vu && v->deja_vu)
				obj->deja_vus[v->id][u->id] = OUT_MODE;
		}
	}
}

int 		apply_algo_bellman_ford(t_objectif *obj, t_solution *sol)
{
	int 		i;
	int 		j;

	t_edge 		*e;
	
	init_dist_deja_vu_lst(obj);

	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		
		// // j = obj->nb_edge_f;
		// j = -1;
		// // while (--j >= 0)
		// while (++j < obj->nb_edge_f)
		// {
		// 	// printf("---%d   %d\n", i, j);
		// 	e = obj->lst_edge_ord[j];
		// 	if (e->direction & UNIDIR1)
		// 		check_bellman_ford(obj, sol, e, 1);
		// 	if (e->direction & UNIDIR2)
		// 		check_bellman_ford(obj, sol, e, 2);	
		// }

		int o;
		o = -1;
				
		// o = obj->nb_node;
		o = -1;
		// while (--o >= 0)
		while (++o < obj->nb_node)
		{
			j = -1;
			while (++j < obj->lst_node[o]->nb_edge_f)
			{
				e = obj->lst_node[o]->edge[j];
				if (obj->lst_node[o] == e->node1 && e->direction & UNIDIR1)
					check_bellman_ford(obj, sol, e, 1);
				else if (obj->lst_node[o] == e->node2 && e->direction & UNIDIR2)
					check_bellman_ford(obj, sol, e, 2);
			}
		}

		if (!obj->dist_up)
			break;
	}
	
	sol->way[sol->nb_way].cost = obj->dists[obj->nb_node - 1];

	if (obj->dists[obj->nb_node - 1] == __INT_MAX__) //|| dist[obj->nb_node - 1] < 0)
		return(0);
	return(1);
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}
