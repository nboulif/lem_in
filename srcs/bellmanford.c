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
	//int 	dir;

	if (mode == 1)
	{
		u = e->node1;
		v = e->node2;
		w = e->w1;
	//	dir = UNIDIR1;
	}
	else
	{
		u = e->node2;
		v = e->node1;
		w = e->w2;
	//	dir = UNIDIR2;
	}
	// if (!v->passage)
	// {
	// if (u->deja_vu)
	// 	printf("UH->deja_vu |%s|\n", u->name);
	// if (v->deja_vu)
	// 	printf("VE->deja_vu |%s|\n", u->name);
	// if (v->deja_vu && u->deja_vu)
	// 	printf("LES 2\n");
	// 	return ;
	// }
	//printf("checking --> (%d)|%s|-(%d)|%s|\n", u->deja_vu, u->name,v->deja_vu, v->name);
	if (
		u != v && u != obj->end_node// && v->passage
		&& v != obj->start_node
		&& (!u->deja_vu || v->deja_vu ||
		(u->father_node_out[sol->nb_way]))// && u->father_node[sol->nb_way]->deja_vu)) &&
		)
	{
		// obj->dist_up = 1; A REFAIRE
		if (u->deja_vu && v->deja_vu)
		{
			//printf("DEJA_VU_NODE --> |%s|-|%s|\n", u->name, v->name);
			if (v->deja_vu == u->deja_vu &&
				(*dist)[u->id] != __INT_MAX__ && (*dist)[u->id] + w < (*dist)[v->id + obj->nb_node])
			{
				//printf("BEM BEM\n");
				obj->dist_up = 1;
				(*dist)[v->id + obj->nb_node] = (*dist)[u->id] + w;
				v->father_node_out[sol->nb_way] = u;
				v->father_edge_out[sol->nb_way] = e;
				v->father_mode = 0;
				if ((*dist)[v->id + obj->nb_node] < (*dist)[v->id] || (*dist)[v->id] == __INT_MAX__)
				{
					(*dist)[v->id] = (*dist)[v->id + obj->nb_node];
					v->father_node[sol->nb_way] = u;
					v->father_edge[sol->nb_way] = e;
				}
			}
		}
		else
		{
			if (u->deja_vu && !v->deja_vu)
			{
				if ((*dist)[u->id + obj->nb_node] == __INT_MAX__ ||
					(*dist)[v->id] <= (*dist)[u->id + obj->nb_node] + w)
					return ;
				(*dist)[v->id] = (*dist)[u->id + obj->nb_node] + w;
				v->father_mode = 1;
				//printf("father |%s|\n", u->name);
			}
			else
			{
				if ((*dist)[u->id] == __INT_MAX__ || (*dist)[u->id] + w >= (*dist)[v->id])
					return ;
				//printf("ici\n");
				(*dist)[v->id] = (*dist)[u->id] + w;
				v->father_mode = 0;
			}
			obj->dist_up = 1;
				//printf("|%s|-|%s| -> %d\n", u->name, v->name,(*dist)[v->id]);
			v->father_node[sol->nb_way] = u;
			v->father_edge[sol->nb_way] = e;
		}
	}
}

void apply_algo_bellman_ford(t_objectif *obj, t_solution *sol, int **dist)
{
	int i;
	int j;

	t_edge *e;
	

	i = -1;
	//printf("FIND_WAY %d\n", sol->nb_way);
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		// j = obj->nb_edge_f;
		j = -1;
		// while (--j >= 0)
		while (++j < obj->nb_edge_f)
		{
			e = obj->lst_edge_ord[j];
			if (e->direction & UNIDIR1)
				check_bellman_ford(obj, sol, dist, e, 1);
			if (e->direction & UNIDIR2)
				check_bellman_ford(obj, sol, dist, e, 2);
		}
		if (!obj->dist_up)
			break ;
	}
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}
