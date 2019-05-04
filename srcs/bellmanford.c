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

void check_negative_cycle(t_objectif *obj, int **dist)
{
	int i;
	int u;
	int v;

	i = -1;
	while (++i < obj->nb_edge)
    {
		u = obj->lst_edge[i].node1->id;
		v = obj->lst_edge[i].node2->id;
        if ((*dist)[u] != __INT_MAX__ && (*dist)[u] + obj->lst_edge[i].w1 < (*dist)[v]) 
            printf("Graph contains negative weight cycle\n"); 
    } 
	
}

void check_bellman_ford(t_objectif *obj, t_solution *sol, int **dist, int*** deja_vu, t_edge *e, int mode)
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
		u != v && u != obj->end_node && v != obj->start_node &&
		(!u->deja_vu || 
			// (
			// 	u->fathers[sol->nb_way].node &&
			// 	(*deja_vu)[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE
			// )
			(
				!v->deja_vu &&
				u->fathers[sol->nb_way].node &&
				(*deja_vu)[u->id][u->fathers[sol->nb_way].node->id] == OUT_MODE
				// u->fathers[sol->nb_way].mode == IN_MODE
			) ||
			(
				v->deja_vu && 
				(
					e->deja_vu //|| (
					// v->fathers[sol->nb_way].node &&
					// v->fathers[sol->nb_way].node == u ) 
				)
			)
		) &&
		// (!u->deja_vu || v->deja_vu || 
		// (u->fathers[sol->nb_way].node && u->fathers[sol->nb_way].node->deja_vu)) &&
		(*dist)[u->id] != __INT_MAX__ && 
		(
			(*dist)[u->id] + w < (*dist)[v->id] 
			|| 
			((*dist)[u->id] + w == (*dist)[v->id] && v->deja_vu)
		)
		)
	{
		
		obj->dist_up = 1;
		(*dist)[v->id] = (*dist)[u->id] + w ;
		//printf("|%s|-|%s| -> %d\n", u->name, v->name,(*dist)[v->id]);

		v->fathers[sol->nb_way].node = u;
		v->fathers[sol->nb_way].edge = e;

		if (!u->deja_vu)
		{
			v->fathers[sol->nb_way].mode = NO_MODE;
			if (v->deja_vu)
				(*deja_vu)[v->id][u->id] = IN_MODE;
			else
				(*deja_vu)[v->id][u->id] = NO_MODE;
		}
		else if (!v->deja_vu)
		{
			(*deja_vu)[v->id][u->id] = NO_MODE;
			v->fathers[sol->nb_way].mode = OUT_MODE;
		}
		else
		{
			(*deja_vu)[v->id][u->id] = OUT_MODE;
			v->fathers[sol->nb_way].mode = IN_MODE;
		}

	}
}

void apply_algo_bellman_ford(t_objectif *obj, t_solution *sol, int **dist)
{
	int i;
	int j;

	t_edge *e;
	
	int		**deja_vu; 

	deja_vu = (int**)malloc(sizeof(int*) * obj->nb_node + 1);
	i = 0;
	while (i < obj->nb_node)
	{
		deja_vu[i] = (int*)malloc(sizeof(int) * obj->nb_node + 1);
		ft_memset(deja_vu[i++], -1, obj->nb_node + 1);
	}
	
	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		
		j = obj->nb_edge_f;
		// j = -1;
		while (--j >= 0)
		// while (++j < obj->nb_edge_f)
		{
			// printf("---%d   %d\n", i, j);
			e = obj->lst_edge_ord[j];
			if (e->direction & UNIDIR1)
				check_bellman_ford(obj, sol, dist, &deja_vu, e, 1);
			if (e->direction & UNIDIR2)
				check_bellman_ford(obj, sol, dist, &deja_vu, e, 2);
		}

		if (!obj->dist_up)
			break;
	}
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}
