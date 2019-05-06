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

int init_dist_lst(t_objectif *obj, int **dist)
{
	if (!((*dist) = (int *)malloc(sizeof(int) * obj->nb_node * 2)))
		return (0);
	for (int i = 0; i < obj->nb_node; i++)
	{
		(*dist)[obj->lst_node[i]->id + obj->nb_node] = __INT_MAX__;
		(*dist)[obj->lst_node[i]->id] = __INT_MAX__;
	}
	(*dist)[obj->start_node->id] = 0;
	(*dist)[obj->start_node->id + obj->nb_node] = 0;
	return (1);
}

void  merge_way(t_solution *sol)
{
	int z;
	t_edge_link *tmp_e;
	t_node_link *tmp_n;
	int i;
	t_edge_link *e_ln_1;
	t_edge_link *e_ln_2;
	t_node_link	*n_ln_1;
	t_node_link *n_ln_2;

	i = -1;
	//printf("merge\n");
	while (++i < sol->way[sol->nb_way].len)
	// while (--i >= 0)
	{
		e_ln_2 = &sol->way[sol->nb_way].edges_lk[i];
		n_ln_2 = &sol->way[sol->nb_way].nodes_lk[i];
		if (e_ln_2->next && e_ln_2->next->edge->direction == NODIR)
		{
			z = sol->nb_way;
			//printf("|%s|-|%s| is NODIR\n", e_ln_2->next->edge->node1->name, e_ln_2->next->edge->node2->name);
			while(z-- > 0)
			{
				e_ln_1 = sol->way[z].edges_lk;
				n_ln_1 = sol->way[z].nodes_lk;
				//printf("cmp ||%s|-|%s|| == ||%s|-|%s||\n", e_ln_2->next->edge->node1->name, e_ln_2->next->edge->node2->name,
				//	 e_ln_1->next->edge->node1->name, e_ln_1->next->edge->node2->name);
				while(e_ln_1->next && (e_ln_1->next->edge != e_ln_2->next->edge))
				{
					e_ln_1 = e_ln_1->next;
					n_ln_1 = n_ln_1->next;
				}
				//printf("cmp ||%s|-|%s|| == ||%s|-|%s||\n", e_ln_2->next->edge->node1->name, e_ln_2->next->edge->node2->name,
				//	 e_ln_1->next->edge->node1->name, e_ln_1->next->edge->node2->name);
				if(e_ln_1->next && (e_ln_1->next->edge == e_ln_2->next->edge))
				{
					tmp_e = e_ln_2->next->next;
					tmp_n = n_ln_2->next->next;
					e_ln_2->next = e_ln_1->next->next;
					n_ln_2->next = n_ln_1->next->next;
					e_ln_1->next = tmp_e;
					n_ln_1->next = tmp_n;
					break;
				}
			}
		}
	}
}

// pour debug uniquement
int	check_in_tab(t_node *new_element)
{
	static t_node	tab[50000];
	static int		index;
	static int		fin = 1;

	if (!fin)
		return (0);
	for (int i = 0; i < index; i++)
	{
		if (tab[i].name == new_element->name)
			return ((fin = 0));
	}
	tab[index++] = *new_element;
	return (1);
}

void set_way_len_with_father_node(t_solution *sol, t_node *end_node)
{
	t_node 	*curr;
	t_way 	*way;
	t_node	*from;

	way = &sol->way[sol->nb_way];
	way->len = 0;
	curr = end_node;
	while ((curr = curr->father_node[sol->nb_way]))
	{
		//if (!curr->deja_vu)
			way->len++;
//if (check_in_tab(curr)) // debug
	printf("boucle infiniiii |%s|\n", curr->name);
		while (curr->father_node_out[sol->nb_way] &&
			(from->father_mode))// || curr->father_node_out[sol->nb_way] == curr->father_node[sol->nb_way]))
		{
			from = curr;
			curr = curr->father_node_out[sol->nb_way];
//if (check_in_tab(curr)) // debug
	printf("boucle infiniiii |%s|\n", curr->name);
		//	if (!curr->deja_vu)
			way->len++;
		}
		from = curr;
	}
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
t_node		*l_node; // last node
t_edge		*l_edge;
	t_edge *e;
	t_way *way;
	int		mode = 0;

	way = &sol->way[sol->nb_way];

	// set_way_len_with_fathers(sol, obj->end_node);
	set_way_len_with_father_node(sol, obj->end_node);

	i = way->len - 1;
	way->nodes_lk[i].node = obj->end_node;
	way->nodes_lk[i].next = NULL;
l_edge = NULL;
l_node = NULL;
	while (i + 1)
	{
		n_ln = &way->nodes_lk[i];
		e_ln = &way->edges_lk[i];
		// printf("name %s \n", n_ln->node->name);
		if (!mode)
			e_ln->edge = n_ln->node->father_edge[sol->nb_way];
		else
			e_ln->edge = n_ln->node->father_edge_out[sol->nb_way];

		e_ln->next = n_ln->node == obj->end_node ? NULL : &way->edges_lk[i + 1];
		
		e_ln->edge->deja_vu += 1;

		if (!mode)
		{
			way->nodes_lk[i - 1].node = n_ln->node->father_node[sol->nb_way];
			mode = n_ln->node->father_mode;
		}
		else
		{
			mode = 0;
			way->nodes_lk[i - 1].node = n_ln->node->father_node_out[sol->nb_way];
		}
		way->nodes_lk[i - 1].next = n_ln;
		if (way->nodes_lk[i - 1].node->id != obj->start_node->id)
			way->nodes_lk[i - 1].node->deja_vu += 1;
		// e = n_ln->node->father_edge[sol->nb_way];
		e = e_ln->edge;

		dir = e->node1->id == n_ln->node->id ? UNIDIR1 : UNIDIR2;
		w = e->node1->id == n_ln->node->id ? &e->w1 : &e->w2;

		e->direction != BIDIR && e->direction != NODIR ? *w = 0 : 0;
		e->direction != BIDIR && e->direction != NODIR ? e->direction = NODIR : 0;

		// e->direction == BIDIR ? obj->offset = 1 : 0;
		// e->direction == BIDIR ? *w = -1 : 0;
		// e->direction == BIDIR ? *w = 0 : 0;
		// e->direction == BIDIR ? *w = -(*w) : 0;
		e->direction == BIDIR ? e->direction = dir : 0;
		l_edge = e_ln->edge;
		l_node = n_ln->node;
		--i;
	}
	return(1);
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
			return (0);
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

						printf("CROISEMENT  |%s| : way %d |%s|-|%s| & %d |%s|-|%s|\n",node->name,
							sol->nb_way, 
							e_ln->edge->node1->name, e_ln->edge->node2->name,
							z, 
							e_check->edge->node1->name, e_check->edge->node2->name
						);
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

int find_way(t_objectif *obj, t_solution *sol)
{ 
	t_way 		*way;
	int			*dist;

	way = &sol->way[sol->nb_way];

	if (!(init_dist_lst(obj, &dist)) || !(init_way(obj, way)))
	    return (-1);

	apply_algo_bellman_ford(obj, sol, &dist);
	//suurballe_formule(obj, &dist, sol);
	if (dist[obj->nb_node - 1] == __INT_MAX__)
		return (0);

	way->cost = dist[obj->nb_node - 1];

	make_way(obj, sol);
	print_way_status_before_merge(way);
	merge_way(sol);	
	//print_way(obj, sol);
	update_ways_len_with_node_lk(sol);
    return (1);
} 