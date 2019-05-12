/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way.c                                              :+:      :+:    :+:   */
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
	t_node	*from;


	way = &sol->way[sol->nb_way];
	way->len = 0;
	curr = end_node;
	from = end_node;
	while ((curr = curr->fathers[sol->nb_way].node))
	{
		//if (!curr->deja_vu)
			way->len++;
//if (check_in_tab(curr)) // debug
//	printf("boucle infiniiii |%s|\n", curr->name);
		while (curr->fathers[sol->nb_way].node_out &&
			(from->father_mode))
			// fathers[sol->nb_way].mode))
			// (from->father_mode))// || curr->fathers[sol->nb_way].node_out == curr->father_node[sol->nb_way]))
		{
			from = curr;
			curr = curr->fathers[sol->nb_way].node_out;
//if (check_in_tab(curr)) // debug
//	printf("boucle infiniiii |%s|\n", curr->name);
		//	if (!curr->deja_vu)
			way->len++;
		}
		from = curr;
	}
}

void 		update_ways_len_with_node_lk(t_solution *sol)
{
	t_edge_link		*e_ln;
	t_node_link		*n_ln;
	int 			i;

	i = -1;
	while (++i <= sol->nb_way)
	{
		sol->way[i].len = 1;
		e_ln = sol->way[i].edges_lk;
		n_ln = sol->way[i].nodes_lk;
		while ((e_ln = e_ln->next))
		{
			n_ln = n_ln->next;
			sol->way[i].len++;
		}
	}
}

void  	    merge_way(t_solution *sol)
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
							if (e_ln_last_b->edge->node1 == e_ln_last_b->next->edge->node1 ||
								e_ln_last_b->edge->node1 == e_ln_last_b->next->edge->node2)
							{
								e_ln_last_b->edge->deja_vu = 0;
								e_ln_last_b->edge->w1 = 1;
								e_ln_last_b->edge->w2 = 1;
								e_ln_last_b->edge->direction = BIDIR;
								e_ln_last_b->next->edge->deja_vu = 0;
								e_ln_last_b->next->edge->w1 = 1;
								e_ln_last_b->next->edge->w2 = 1;
								e_ln_last_b->next->edge->direction = BIDIR;
								e_ln_last_b->edge->node1->deja_vu = 0;
							}
							else if (e_ln_last_b->edge->node2 == e_ln_last_b->next->edge->node1 ||
									e_ln_last_b->edge->node2 == e_ln_last_b->next->edge->node2)
							{
								e_ln_last_b->next->edge->deja_vu = 0;
								e_ln_last_b->next->edge->w1 = 1;
								e_ln_last_b->next->edge->w2 = 1;
								e_ln_last_b->next->edge->direction = BIDIR;
								e_ln_last_b->edge->deja_vu = 0;
								e_ln_last_b->edge->w1 = 1;
								e_ln_last_b->edge->w2 = 1;
								e_ln_last_b->edge->direction = BIDIR;
								e_ln_last_b->edge->node2->deja_vu = 0;
							}
							e_ln_last_b = e_ln_last_b->next;
							e_ln_old_b = e_ln_old_b->prev;
							i++;
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
int make_iter = 0;
int 	    make_way(t_objectif *obj, t_solution *sol)
{
	int i;
	int dir;
	int *w;
	t_node_link *n_ln;
	t_edge_link *e_ln;
	t_edge *e;
	t_way *way;

	int		mode;
		
	mode = 0;

	way = &sol->way[sol->nb_way];
	set_way_len_with_fathers(sol, obj->end_node);	
	i = way->len - 1;
	way->nodes_lk[i].node = obj->end_node;
	way->nodes_lk[i].next = NULL;
	mode = obj->end_node->father_mode;
	while (i + 1)
	{
		n_ln = &way->nodes_lk[i];
		e_ln = &way->edges_lk[i];
		//printf ("make way iter %d\n", way->len - i);
		if (!mode)
			e_ln->edge = n_ln->node->fathers[sol->nb_way].edge;
		else
		{
			// printf("\n");
			e_ln->edge = n_ln->node->fathers[sol->nb_way].edge_out;
		}
		//printf("egde selected\n");
		e_ln->edge->deja_vu += 1;
		e_ln->next = n_ln->node == obj->end_node ? NULL : &way->edges_lk[i + 1];
		e_ln->prev = i == 0 ? NULL : &way->edges_lk[i - 1];
		//printf("egde next and prev set\nmode ==");
		if (!mode)
		{
			//printf(" 0\n");
			way->nodes_lk[i - 1].node = n_ln->node->fathers[sol->nb_way].node;
			//printf("way->nodes_lk ok\n");
			mode = n_ln->node->father_mode;
			// n_ln->node->fathers[sol->nb_way].mode;
		}
		else
		{
			//printf(" 1\n");
			way->nodes_lk[i - 1].node = n_ln->node->fathers[sol->nb_way].node_out;
			//printf("way->nodes_lk ok\n");
			mode = 0;
		}
		//printf("node selected |%s|\n", way->nodes_lk[i - 1].node->name);
		// for (int x = 0;x < 10000; x++)
		// 	printf("");
		// 	;
		//if (make_iter >= 2)
		//	sleep(1);
		way->nodes_lk[i - 1].next = n_ln;
		
		if (way->nodes_lk[i - 1].node->id != obj->start_node->id &&
			way->nodes_lk[i - 1].node->id != obj->end_node->id)
			way->nodes_lk[i - 1].node->deja_vu += 1;

		e = e_ln->edge;

		dir = e->node1->id == n_ln->node->id ? UNIDIR2 : UNIDIR1;
		w = e->node1->id == n_ln->node->id ? &e->w1 : &e->w2;

		
		// e->direction != BIDIR && e->direction != NODIR ? *w = 0 : 0;
		// e->direction != BIDIR && e->direction != NODIR ? e->direction = NODIR : 0;

		// e->direction == BIDIR ? obj->offset = 1 : 0;
		e->direction == BIDIR ? *w = -1 : 0;
		e->direction -= dir;
		// e->direction == BIDIR ? *w = 0 : 0;
		// e->direction == BIDIR ? *w = -1 : 0;
		//e->direction == BIDIR ? e->direction = dir : 0;

		--i;
	}
	make_iter++;
	return(1);
}
