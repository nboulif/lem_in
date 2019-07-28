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
	for (int i = 0; i < obj->nb_node; i++)
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
// pour debug uniquement
// int	check_in_tab(t_node *new_element)
// {
// 	static t_node	tab[50000];
// 	static int		index;
// 	static int		fin = 1;

// 	if (!fin)
// 		return (0);
// 	if (index == 0)
// 		ft_bzero(tab, 50000 * sizeof(int));
// 	for (int i = 0; i < index; i++)
// 	{
// 		if (tab[i].name == new_element->name)
// 			return ((fin = 0));
// 	}
// 	tab[index++] = *new_element;
// 	return (1);
// }

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

void 	check_bellman_ford(t_objectif *obj, t_solution *sol, t_edge *e, int mode)
{
	t_node *u;
	t_node *v;
	int 	w;

	if (mode == 1)
	{
		u =	e->node1;
		v =	e->node2;
		w = e->w1;
	}
	else
	{
		u =	e->node2;
		v =	e->node1;
		w = e->w2;
	}
	if (u != v && u != obj->end_node
		&& v != obj->start_node
		&& (!u->deja_vu || v->deja_vu ||
		(u->fathers[sol->nb_way].node_out)))
	{
		if (u->deja_vu && v->deja_vu)
		{
			if (e->deja_vu && obj->dists[u->id] != __INT_MAX__ &&
				obj->dists[u->id] + w < obj->dists[v->id + obj->nb_node])
			{
				obj->dist_up = 1;
				obj->dists[v->id + obj->nb_node] = obj->dists[u->id] + w;
				v->fathers[sol->nb_way].node_out = u;
				v->fathers[sol->nb_way].edge_out = e;
				v->father_mode = 0;
				if (obj->dists[v->id + obj->nb_node] < obj->dists[v->id] || obj->dists[v->id] == __INT_MAX__)
				{
					obj->dists[v->id] = obj->dists[v->id + obj->nb_node];
					v->fathers[sol->nb_way].node = u;
					v->fathers[sol->nb_way].edge = e;
					v->fathers[sol->nb_way].mode = 0;
				}
			}
		}
		else
		{
			if (u->deja_vu && !v->deja_vu)
			{
				if (obj->dists[u->id + obj->nb_node] == __INT_MAX__ ||
					obj->dists[v->id] <= obj->dists[u->id + obj->nb_node] + w)
					return ;
				obj->dists[v->id] = obj->dists[u->id + obj->nb_node] + w;
				v->father_mode = 1;
			}
			else
			{
				if (obj->dists[u->id] == __INT_MAX__ ||
					obj->dists[u->id] + w >= obj->dists[v->id])
					return ;
				obj->dists[v->id] = obj->dists[u->id] + w;
				v->father_mode = 0;
			}
			obj->dist_up = 1;
			v->fathers[sol->nb_way].node = u;
			v->fathers[sol->nb_way].edge = e;
		}
	}
}

int 		apply_algo_bellman_ford(t_objectif *obj, t_solution *sol)
{
	int 		i;
	int 		j;
	int			o;	

	t_edge 		*e;

	init_dist_deja_vu_lst(obj);
	i = -1;
	while (++i < obj->nb_node)
	{
		obj->dist_up = 0;
		o = -1;
		while (++o < obj->nb_node)
		{
			j = -1;
			while (++j < obj->lst_node[o]->nb_edge_f)
			{
				e = obj->lst_node[o]->edge[j];
				if (e->direction == NODIR)
					continue ;
				if (obj->lst_node[o] == e->node1 && e->direction & UNIDIR1)
					check_bellman_ford(obj, sol, e, 1);
				else if (obj->lst_node[o] == e->node2 && e->direction & UNIDIR2)
					check_bellman_ford(obj, sol, e, 2);
			}
		}
		if (!obj->dist_up)
			break;
	}
	//suurballe_formule(obj, sol->nb_way);
	sol->way[sol->nb_way].cost = obj->dists[obj->nb_node - 1];

	if (obj->dists[obj->nb_node - 1] == __INT_MAX__) //|| dist[obj->nb_node - 1] < 0)
		return(0);
	return(1);
	// printf("- \n");
	// check_negative_cycle(obj, dist);
}
