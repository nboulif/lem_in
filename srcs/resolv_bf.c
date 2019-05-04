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

void set_way_len_with_fathers(t_solution *sol, t_node *end_node)
{
	t_node 	*curr;
	t_way 	*way;

	way = &sol->way[sol->nb_way];
	way->len = 0;
	curr = end_node;
	while ((curr = curr->fathers[sol->nb_way].node))
		way->len++;
	
}


void update_ways_len_with_node_lk(t_solution *sol)
{
	t_edge_link		*e_ln;
	int 			i;

	i = -1;
	while (++i <= sol->nb_way)
	{
		sol->way[i].len = 1;
		e_ln = &sol->way[i].edges_lk[0];
		while ((e_ln = e_ln->next))
			sol->way[i].len++;
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
	// t_edge_link *tmp;
	int i;
	t_edge_link *e_ln_old_a;
	t_edge_link *e_ln_old_b;
	t_edge_link *e_ln_last_a;
	t_edge_link *e_ln_last_b;

	i = -1;
	// i = sol->way[sol->nb_way].len;
	while (++i < sol->way[sol->nb_way].len)
	// while (--i >= 0)
	{
		e_ln_last_a = &sol->way[sol->nb_way].edges_lk[i];
		if (e_ln_last_a->edge && e_ln_last_a->edge->direction == NODIR)
		{
			z = sol->nb_way;
			while(z-- > 0)
			{
				e_ln_old_a = sol->way[z].edges_lk;
				while(e_ln_old_a && (e_ln_old_a->edge != e_ln_last_a->edge))
					e_ln_old_a = e_ln_old_a->next;
				if(e_ln_old_a && (e_ln_old_a->edge == e_ln_last_a->edge))
				{
					e_ln_last_b = e_ln_last_a;
					e_ln_old_b = e_ln_old_a;
					if (e_ln_last_a->next && e_ln_last_a->next->edge->direction == NODIR &&
						e_ln_old_a->prev && e_ln_old_a->prev->edge == e_ln_last_a->next->edge)
					{
						while (e_ln_old_b->prev->edge == e_ln_last_b->next->edge)
						{
							e_ln_last_b = e_ln_last_b->next;
							e_ln_old_b = e_ln_old_b->prev;
						}
					}
					e_ln_old_a->next->prev = e_ln_last_a->prev;
					e_ln_last_a->prev->next = e_ln_old_a->next;
					e_ln_old_b->prev->next = e_ln_last_b->next;
					e_ln_last_b->next->prev = e_ln_old_b->prev;
					break;
				}
			}
		}
	}
	update_ways_len_with_node_lk(sol);
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

	set_way_len_with_fathers(sol, obj->end_node);
	// set_way_len_with_father_node(sol, obj->end_node);
	
	i = way->len - 1;
	way->nodes_lk[i].node = obj->end_node;
	way->nodes_lk[i].next = NULL;
	
	while (i + 1)
	{
		n_ln = &way->nodes_lk[i];
		e_ln = &way->edges_lk[i];
		
		e_ln->edge = n_ln->node->fathers[sol->nb_way].edge;
		e_ln->next = n_ln->node == obj->end_node ? NULL : &way->edges_lk[i + 1];
		e_ln->prev = i == 0 ? NULL : &way->edges_lk[i - 1];
		e_ln->edge->deja_vu += 1;

		way->nodes_lk[i - 1].node = n_ln->node->fathers[sol->nb_way].node;

		way->nodes_lk[i - 1].next = n_ln;
		if (way->nodes_lk[i - 1].node->id != obj->start_node->id)
			way->nodes_lk[i - 1].node->deja_vu += 1;
		
		e = n_ln->node->fathers[sol->nb_way].edge;

		dir = e->node1->id == n_ln->node->id ? UNIDIR1 : UNIDIR2;
		w = e->node1->id == n_ln->node->id ? &e->w1 : &e->w2;

		e->direction != BIDIR && e->direction != NODIR ? *w = 0 : 0;
		e->direction != BIDIR && e->direction != NODIR ? e->direction = NODIR : 0;

		// e->direction == BIDIR ? obj->offset = 1 : 0;
		// e->direction == BIDIR ? *w = -(*w) : 0;
		// e->direction == BIDIR ? *w = 0 : 0;
		e->direction == BIDIR ? *w = -(*w) : 0;
		e->direction == BIDIR ? e->direction = dir : 0;

		--i;
	}

	return(1);
}


int check_atomic(t_objectif *obj, t_solution *sol, t_way *way)
{
	t_edge_link		*e_check;
	int 			z;
	
	t_edge_link 	*e_ln;
	t_node			*node;
	int 			check;
	
	check = 1;
	printf("len => %d\n", way->len);

	e_ln = &way->edges_lk[0];
	node = obj->start_node;
	while (e_ln)
	{
		node = get_right_node_in_edge(e_ln->edge, node, 0);

		if (e_ln->next && !node)
		{
			printf("DISCONTINUE\n");
			check = 0;
		}
		if (node)
		{
			z = -1;
			while(++z < sol->nb_way)
			{
				e_check = sol->way[z].edges_lk;
				t_node *node_checker = obj->start_node;
				while (e_check)
				{
					node_checker = get_right_node_in_edge(e_check->edge, node_checker, 0);
					if (node_checker == node && node != obj->end_node && node)
					{
						printf("CROISEMENT way %d&%d : |%s|\n", sol->nb_way, z, node->name);
						check = 0;
					}
					e_check = e_check->next;
				}
			}
		
		}
		e_ln = e_ln->next;
	}
	
	return (check);
}

void print_way_status_after_merge(t_objectif *obj, t_way *way)
{
	t_edge_link *e_ln;
	t_node		*node;
	
	printf("len => %d\n", way->len);

	e_ln = &way->edges_lk[0];
	node = obj->start_node;
	while (e_ln)
	{
		node = get_right_node_in_edge(e_ln->edge, node, 0);

		printf("dv %d %s   %s -- %s   / w  %d -- %d  / dir  %d \n", 
			node->deja_vu, node->name,
			e_ln->edge->node1->name, e_ln->edge->node2->name, 
			e_ln->edge->w1, e_ln->edge->w2,			
			e_ln->edge->direction			
			);
		e_ln = e_ln->next;
	}
}

void print_way_status_before_merge(t_way *way)
{
	int i;
	
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
	if (dist[obj->nb_node - 1] == __INT_MAX__) //|| dist[obj->nb_node - 1] < 0)
		return(0);

	way->cost = dist[obj->nb_node - 1];

	printf("cost => %d\n", way->cost);
	
	make_way(obj, sol);
	print_way_status_before_merge(way);
	merge_way(sol);	
	if (check_atomic(obj, sol, way))
	{
		print_way_status_after_merge(obj, way);
		return (1);
	}
	else
	{
		printf("\n\nCROSSSSSSSSSSSSSSSSSSING\n\n");	
		return (0);
	}
	
} 