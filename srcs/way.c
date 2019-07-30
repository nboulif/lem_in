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
	int 			i;

	i = -1;
	while (++i <= sol->nb_way)
	{
		sol->way[i].len = 1;
		e_ln = sol->way[i].edges_lk;
		while ((e_ln = e_ln->next))
			sol->way[i].len++;
	}
}

t_node 		*get_node_between_2_edge(t_edge *edge1, t_edge *edge2)
{
	if (edge1->node1 == edge2->node1 || edge1->node1 == edge2->node2)
		return (edge1->node1);
	return (edge1->node2);
}

void		merge_multiple_disc_edge(t_objectif *obj, t_edge_link *e_ln_last_a, t_edge_link *e_ln_old_a, 
						 			 t_edge_link *e_ln_last_b, t_edge_link *e_ln_old_b)
{
	t_edge_link *e_ln_old_a1;
	t_edge_link *e_ln_old_b1;
	t_edge_link *e_ln_last_a1;
	t_edge_link *e_ln_last_b1;

	e_ln_old_a1 = e_ln_old_b->prev;
	e_ln_old_b1 = e_ln_old_b->prev;

	e_ln_last_a1 = e_ln_last_b;	

	int i;
	i = -1;
	while (++i < obj->sol->way[obj->sol->nb_way].len && e_ln_old_a1->edge != e_ln_last_a1->edge)
		e_ln_last_a1 = &obj->sol->way[obj->sol->nb_way].edges_lk[i];
	
	
	e_ln_last_b1 = e_ln_last_a1;
	while (e_ln_old_b1->prev->edge == e_ln_last_b1->next->edge)
	{
		e_ln_old_b1 = e_ln_old_b1->prev;
		e_ln_last_b1 = e_ln_last_b1->next;
	}

	e_ln_old_b1->prev->next = e_ln_last_b1->next;
	e_ln_last_b1->next->prev = e_ln_old_b1->prev;

	e_ln_old_a->next->prev = e_ln_last_a->prev;
	e_ln_last_a->prev->next = e_ln_old_a->next;

	e_ln_last_a1->prev->next = e_ln_last_b->next;
	e_ln_last_b->next->prev = e_ln_last_a1->prev;
}

int			pass_next_nodirs(t_edge_link *e_ln_last_a, t_edge_link *e_ln_old_a, 
						 	 t_edge_link **e_ln_last_b, t_edge_link **e_ln_old_b)
{
	int i;
	
	(*e_ln_last_b) = e_ln_last_a;
	(*e_ln_old_b) = e_ln_old_a;
	
	i = 0;

	while ((*e_ln_old_b)->prev->edge == (*e_ln_last_b)->next->edge)
	{


		get_node_between_2_edge((*e_ln_last_b)->edge, (*e_ln_last_b)->next->edge)->deja_vu = 0;
		
		(*e_ln_last_b)->edge->deja_vu = 0;
		(*e_ln_last_b)->edge->w1 = 1;
		(*e_ln_last_b)->edge->w2 = 1;
		(*e_ln_last_b)->edge->direction = BIDIR;

		(*e_ln_last_b)->next->edge->deja_vu = 0;
		(*e_ln_last_b)->next->edge->w1 = 1;
		(*e_ln_last_b)->next->edge->w2 = 1;
		(*e_ln_last_b)->next->edge->direction = BIDIR;
	
		(*e_ln_last_b) = (*e_ln_last_b)->next;
		(*e_ln_old_b) = (*e_ln_old_b)->prev;
		i++;
	}
	return (i);
}


int			merge_multiple_edge(t_objectif *obj, t_edge_link *e_ln_last_a, t_edge_link *e_ln_old_a)
{
	int i;

	t_edge_link *e_ln_last_b;
	t_edge_link *e_ln_old_b;
	
	t_node *node_in;
	t_node *node_out;

	node_in = get_node_between_2_edge(e_ln_last_a->edge, e_ln_last_a->prev->edge);
	i = pass_next_nodirs(e_ln_last_a, e_ln_old_a, &e_ln_last_b, &e_ln_old_b);
	node_out = get_node_between_2_edge(e_ln_last_b->edge, e_ln_last_b->next->edge);

	if (node_in->deja_vu_in_way > 1 || node_out->deja_vu_in_way > 1)
	{
		printf("SPECIAL MERGE MULTI 1\n");
		if (node_in->deja_vu_in_way > 1 && !(node_in->deja_vu_in_way % 2))
			node_in->deja_vu_in_way += 1;
		else
		{
			printf("SPECIAL MERGE MULTI 2\n");
			merge_multiple_disc_edge(obj, e_ln_last_a, e_ln_old_a, e_ln_last_a, e_ln_old_a);
			node_out->deja_vu_in_way -= 3;
		}
	}
	else
	{
		e_ln_old_a->next->prev = e_ln_last_a->prev;
		e_ln_old_b->prev->next = e_ln_last_b->next;

		e_ln_last_a->prev->next = e_ln_old_a->next;
		e_ln_last_b->next->prev = e_ln_old_b->prev;
	}

	return (i);
}

void		merge_one_edge(t_objectif *obj, t_edge_link *e_ln_last_a, t_edge_link *e_ln_old_a)
{
	
	t_node *node_in;
	t_node *node_out;

	if (e_ln_last_a->edge->node1->deja_vu_in_way > 1 || e_ln_last_a->edge->node2->deja_vu_in_way > 1)
	{

		node_in = get_node_between_2_edge(e_ln_last_a->edge, e_ln_last_a->prev->edge);
		node_out = get_right_node_in_edge(e_ln_last_a->edge, node_in, 0);

		printf("SPECIAL MERGE ONE 1\n");
		if (node_in->deja_vu_in_way > 1 && !(node_in->deja_vu_in_way % 2))
			node_in->deja_vu_in_way += 1;
		else
		{
			printf("SPECIAL MERGE ONE 2\n");
			merge_multiple_disc_edge(obj, e_ln_last_a, e_ln_old_a, e_ln_last_a, e_ln_old_a);
			node_out->deja_vu_in_way -= 3;
		}
	}
	else
	{
		e_ln_old_a->next->prev = e_ln_last_a->prev;
		e_ln_old_a->prev->next = e_ln_last_a->next;

		e_ln_last_a->prev->next = e_ln_old_a->next;
		e_ln_last_a->next->prev = e_ln_old_a->prev;
	}
}

void  	    merge_way(t_objectif *obj, t_solution *sol)
{
	int z;
	// t_edge_link *tmp;
	int i;
	int finish;	

	t_edge_link *e_ln_last;
	t_edge_link *e_ln_old;

	obj->sol = sol;

	while (1)
	{
		finish = 1;

		i = -1;
		// i = sol->way[sol->nb_way].len;

		while (++i < sol->way[sol->nb_way].len)
		// while (--i >= 0)
		{
			e_ln_last = &sol->way[sol->nb_way].edges_lk[i];
			if (e_ln_last->edge && e_ln_last->edge->direction == NODIR)
			{
				z = sol->nb_way;
				while(z-- > 0)
				{
					e_ln_old = sol->way[z].edges_lk;
					while(e_ln_old && (e_ln_old->edge != e_ln_last->edge))
						e_ln_old = e_ln_old->next;
					if(e_ln_old && (e_ln_old->edge == e_ln_last->edge))
					{
						finish = 0;
						if (e_ln_last->next && e_ln_old->prev &&
						e_ln_old->prev->edge == e_ln_last->next->edge)
							i += merge_multiple_edge(obj, e_ln_last, e_ln_old);
						else
							merge_one_edge(obj, e_ln_last, e_ln_old);
						break;
					}
				}
			}
		}
		if (finish)
			break;		
	}
	update_ways_len_with_node_lk(sol);
}

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
		
		if (!mode)
			e_ln->edge = n_ln->node->fathers[sol->nb_way].edge;
		else
		{
			e_ln->edge = n_ln->node->fathers[sol->nb_way].edge_out;
		}
		e_ln->edge->deja_vu += 1;
		e_ln->next = n_ln->node == obj->end_node ? NULL : &way->edges_lk[i + 1];
		e_ln->prev = i == 0 ? NULL : &way->edges_lk[i - 1];
		
		if (!mode)
		{
			i > 0 ? way->nodes_lk[i - 1].node = n_ln->node->fathers[sol->nb_way].node : 0;
			mode = n_ln->node->father_mode;
		}
		else
		{
			i > 0 ? way->nodes_lk[i - 1].node = n_ln->node->fathers[sol->nb_way].node_out : 0;
			mode = 0;
		}

		if (i > 0)
		{
			way->nodes_lk[i - 1].next = n_ln;
			
			if (way->nodes_lk[i - 1].node->id != obj->start_node->id &&
				way->nodes_lk[i - 1].node->id != obj->end_node->id)
			{
				way->nodes_lk[i - 1].node->deja_vu += 1;
				way->nodes_lk[i - 1].node->deja_vu_in_way += 1;		
			}
		}
		

		e = e_ln->edge;

		dir = e->node1->id == n_ln->node->id ? UNIDIR2 : UNIDIR1;
		w = e->node1->id == n_ln->node->id ? &e->w1 : &e->w2;

		
		// e->direction != BIDIR && e->direction != NODIR ? *w = 0 : 0;
		// e->direction != BIDIR && e->direction != NODIR ? e->direction = NODIR : 0;

		// e->direction == BIDIR ? obj->offset = 1 : 0;
		e->direction == BIDIR ? *w = -(*w) : 0;
		e->direction -= dir;
		// e->direction == BIDIR ? *w = 0 : 0;
		// e->direction == BIDIR ? *w = -1 : 0;
		//e->direction == BIDIR ? e->direction = dir : 0;

		--i;
	}

	return(1);
}
