/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_bf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:29:24 by nboulif          ###   ########.fr       */
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
int init_dist_lst(t_objectif *obj, int **dist)
{
	(*dist) = (int *)malloc(sizeof(int) * obj->nb_node);
	for (int i = 0; i < obj->nb_node; i++)
	{
		if (obj->lst_node[i]->id == obj->start_node->id)
			(*dist)[obj->lst_node[i]->id] = 0;
		else
			(*dist)[obj->lst_node[i]->id] = __INT_MAX__;	
	}
	return (1);
}

void  merge_way(t_solution *sol)
{
	int z;
	t_edge_link *tmp;
	int i;
	t_edge_link *e_ln_1;
	t_edge_link *e_ln_2;

	i = -1;
	while (++i < sol->way[sol->nb_way].len)
	{
		e_ln_2 = &sol->way[sol->nb_way].edges_lk[i];
		if (e_ln_2->next && e_ln_2->next->edge->direction == NODIR)
		{
			z = sol->nb_way;
			while(z-- > 0)
			{
				e_ln_1 = sol->way[z].edges_lk;
				while(e_ln_1->next && (e_ln_1->next->edge != e_ln_2->next->edge))
					e_ln_1 = e_ln_1->next;
				if(e_ln_1->next && (e_ln_1->next->edge == e_ln_2->next->edge))
				{
					tmp = e_ln_2->next->next;
					e_ln_2->next = e_ln_1->next->next;
					e_ln_1->next = tmp;
					break;
				}
			}
		}
	}
}

void set_way_len_with_father_node(t_solution *sol, t_node *end_node)
{
	t_node 	*curr;
	t_way 	*way;

	way = &sol->way[sol->nb_way];
	way->len = 0;
	curr = end_node;
	while ((curr = curr->father_node[sol->nb_way]))
		way->len++;
}

void update_ways_len_with_node_lk(t_solution *sol)
{
	t_edge_link		*e_ln;
	int 			i;

	i = -1;
	while (++i < sol->nb_way)
	{
		sol->way[i].len = 1;
		e_ln = &sol->way[i].edges_lk[0];
		while ((e_ln = e_ln->next))
			sol->way[i].len++;
	}
}

int make_way(t_objectif *obj, t_solution *sol)
{
	int i;
	int dir;
	int *w;
	t_node_link *n_ln;
	t_edge_link *e_ln;
	t_edge *e;
	t_way *way;

	way = &sol->way[sol->nb_way];

	set_way_len_with_father_node(sol, obj->end_node);
	
	i = way->len - 1;
	way->nodes_lk[i].node = obj->end_node;
	way->nodes_lk[i].next = NULL;
	
	while (i + 1)
	{
		n_ln = &way->nodes_lk[i];
		e_ln = &way->edges_lk[i];
		// printf("name %s \n", n_ln->node->name);
		
		e_ln->edge = n_ln->node->father_edge[sol->nb_way];
		e_ln->next = n_ln->node == obj->end_node ? NULL : &way->edges_lk[i + 1];
		e_ln->edge->deja_vu += 1;

		way->nodes_lk[i - 1].node = n_ln->node->father_node[sol->nb_way];
		way->nodes_lk[i - 1].next = n_ln;
		if(way->nodes_lk[i - 1].node->id != obj->start_node->id)
			way->nodes_lk[i - 1].node->deja_vu += 1;
		
		e = n_ln->node->father_edge[sol->nb_way];

		dir = e->node1->id == n_ln->node->id ? UNIDIR1 : UNIDIR2;
		w = e->node1->id == n_ln->node->id ? &e->w1 : &e->w2;

		e->direction != BIDIR && e->direction != NODIR ? *w = 0 : 0;
		e->direction != BIDIR && e->direction != NODIR ? e->direction = NODIR : 0;
		
		e->direction == BIDIR ? *w = -(*w) : 0;
		e->direction == BIDIR ? e->direction = dir : 0;

		--i;
	}

	return(1);
}


void print_way_status_before_merge(t_way *way)
{
	int i;
	
	printf("cost => %d\n", way->cost);
	printf("len => %d\n", way->len);

	i = -1;
	while (++i < way->len)
	{
		printf("dv %d %s   %s -- %s   / w  %d -- %d  / dir  %d \n", 
			way->nodes_lk[i].node->deja_vu, way->nodes_lk[i].node->name, 
			way->edges_lk[i].edge->node1->name, way->edges_lk[i].edge->node2->name, 
			way->edges_lk[i].edge->w1, way->edges_lk[i].edge->w2,			
			way->edges_lk[i].edge->direction			
			);
	}
}

int find_way(t_objectif *obj, t_solution *sol)
{ 
    int			*dist; 
	t_way 		*way;

	way = &sol->way[sol->nb_way];

	if (!(init_dist_lst(obj, &dist)) || !(init_way(obj, way)))
	    return (-1);

	apply_algo_bellman_ford(obj, sol, &dist);
	if (dist[obj->nb_node - 1] == __INT_MAX__)
		return(0);

	way->cost = dist[obj->nb_node - 1];

	
	make_way(obj, sol);
	print_way_status_before_merge(way);
	merge_way(sol);	
	update_ways_len_with_node_lk(sol);
    return (1);
} 