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

int init_dist_deja_vu_lst(t_objectif *obj)
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

void check_negative_cycle(t_objectif *obj)
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

void check_bellman_ford(t_objectif *obj, t_solution *sol, t_edge *e, int mode, int **dist)
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

	if (
		u != v && u != obj->end_node
		&& (!u->deja_vu || v->deja_vu || 
		(u->father_node_out[sol->nb_way]))// && u->father_node[sol->nb_way]->deja_vu)) &&
		// (e->direction == BIDIR || e->direction == dir) &&
		// ( 
		// !u->deja_vu || !u->father_node[sol->nb_way] || 
		// 	( 
		// 		( 
		// 			(!v->deja_vu && u->father_node[sol->nb_way]->deja_vu) 
		// 			|| 
		// 			(v->deja_vu && !u->father_node[sol->nb_way]->deja_vu) 
		// 		)
		// 	)
		// ) &&
		// (*dist)[u->id] != __INT_MAX__ && (*dist)[u->id] + w < (*dist)[v->id]
		)
	{
		// obj->dist_up = 1; A REFAIRE
		if (u->deja_vu && v->deja_vu)
		{
			if ((*dist)[u->id] != __INT_MAX__ && (*dist)[u->id] + w < (*dist)[v->id + obj->nb_node])
			{
				obj->dist_up = 1;
				(*dist)[v->id + obj->nb_node] = (*dist)[u->id] + w;
				v->father_node_out[sol->nb_way] = u;
				v->father_edge_out[sol->nb_way] = e;
				v->father_mode = 0;
				if ((*dist)[v->id + obj->nb_node] < (*dist)[v->id])
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
			}
			else
			{
				if ((*dist)[u->id] == __INT_MAX__ || (*dist)[u->id] + w >= (*dist)[v->id])
					return ;
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



int apply_algo_bellman_ford(t_objectif *obj, t_solution *sol, int **dist)
{
	int 		i;
	int 		j;

	t_edge 		*e;
	
	//init_dist_deja_vu_lst(obj);

	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		// j = obj->nb_edge_f;
		j = -1;
		// while (--j >= 0)
		while (++j < obj->nb_edge_f)
		{
			// printf("---%d   %d\n", i, j);
			e = obj->lst_edge_ord[j];
			// printf("check_direction\n");
			if (e->direction & UNIDIR1)
				check_bellman_ford(obj, sol, e, 1, dist);
			if (e->direction & UNIDIR2)
				check_bellman_ford(obj, sol, e, 2, dist);
			// printf("OK \n");
		}
		if (!obj->dist_up)
			break;
	}
	printf("apres boucle\n");
	sol->way[sol->nb_way].cost = (*dist)[obj->nb_node - 1];
	//sol->way[sol->nb_way].cost = obj->dists[obj->nb_node - 1];
	if ((*dist)[obj->nb_node - 1] == __INT_MAX__ || (*dist)[obj->nb_node - 1] < 0)
	//(obj->dists[obj->nb_node - 1] == __INT_MAX__) //|| dist[obj->nb_node - 1] < 0)
		return(0);
	return (1);
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}

void suurballe_formule(t_objectif *obj,	int **dist, t_solution *sol)
{
	int i;
	//int			x;
	t_node *node;

 	i = 0;
	while (i < obj->nb_node)
	{
		node = obj->lst_node[i++];
		if (node->father_edge[sol->nb_way])
		{
			node->father_edge[sol->nb_way]->w1 = node->father_edge[sol->nb_way]->w1 -
												(*dist)[node->father_edge[sol->nb_way]->node2->id] + (*dist)[node->father_edge[sol->nb_way]->node1->id];
			node->father_edge[sol->nb_way]->w2 = node->father_edge[sol->nb_way]->w2 -
												(*dist)[node->father_edge[sol->nb_way]->node1->id] + (*dist)[node->father_edge[sol->nb_way]->node2->id];
		}
		if (node->father_edge_out[sol->nb_way])
		{
			node->father_edge_out[sol->nb_way]->w1 = node->father_edge[sol->nb_way]->w1 -
												(*dist)[node->father_edge[sol->nb_way]->node2->id + obj->nb_node] + (*dist)[node->father_edge[sol->nb_way]->node1->id + obj->nb_node];
			node->father_edge_out[sol->nb_way]->w2 = node->father_edge[sol->nb_way]->w2 -
												(*dist)[node->father_edge[sol->nb_way]->node1->id + obj->nb_node] + (*dist)[node->father_edge[sol->nb_way]->node2->id + obj->nb_node];
		}
	}
}