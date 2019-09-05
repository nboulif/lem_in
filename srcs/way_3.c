/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:34:53 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_way_len_with_fathers(t_solution *sol, t_node *end_node)
{
	t_node	*curr;
	t_way	*way;
	t_node	*from;

	way = &sol->way[sol->nb_way];
	way->len = 0;
	curr = end_node;
	from = end_node;
	while ((curr = curr->fathers[sol->nb_way].node))
	{
		way->len++;
		while (curr->fathers[sol->nb_way].node_out &&
			(from->father_mode))
		{
			from = curr;
			curr = curr->fathers[sol->nb_way].node_out;
			way->len++;
		}
		from = curr;
	}
}

void		update_ways_len_with_node_lk(t_solution *sol)
{
	t_edge_link		*e_ln;
	int				i;

	i = -1;
	while (++i <= sol->nb_way)
	{
		sol->way[i].len = 1;
		e_ln = sol->way[i].edges_lk;
		while ((e_ln = e_ln->next))
			sol->way[i].len++;
	}
}

t_node		*get_node_between_2_edge(t_edge *edge1, t_edge *edge2)
{
	if (edge1->node1 == edge2->node1 || edge1->node1 == edge2->node2)
		return (edge1->node1);
	return (edge1->node2);
}

void		merge_multiple_disc_edge(t_solution *sol, t_e_ln_utils *e_ln_u)
{
	t_edge_link	*e_ln_old_a1;
	t_edge_link	*e_ln_old_b1;
	t_edge_link	*e_ln_last_a1;
	t_edge_link	*e_ln_last_b1;
	int			i;

	e_ln_old_a1 = e_ln_u->e_ln_old_b->prev;
	e_ln_old_b1 = e_ln_u->e_ln_old_b->prev;
	e_ln_last_a1 = e_ln_u->e_ln_last_b;
	i = -1;
	while (++i < sol->way[sol->nb_way].len &&
		e_ln_old_a1->edge != e_ln_last_a1->edge)
		e_ln_last_a1 = &sol->way[sol->nb_way].edges_lk[i];
	e_ln_last_b1 = e_ln_last_a1;
	while (e_ln_old_b1->prev->edge == e_ln_last_b1->next->edge)
	{
		e_ln_old_b1 = e_ln_old_b1->prev;
		e_ln_last_b1 = e_ln_last_b1->next;
	}
	e_ln_old_b1->prev->next = e_ln_last_b1->next;
	e_ln_last_b1->next->prev = e_ln_old_b1->prev;
	e_ln_u->e_ln_old_a->next->prev = e_ln_u->e_ln_last_a->prev;
	e_ln_u->e_ln_last_a->prev->next = e_ln_u->e_ln_old_a->next;
	e_ln_last_a1->prev->next = e_ln_u->e_ln_last_b->next;
	e_ln_u->e_ln_last_b->next->prev = e_ln_last_a1->prev;
}

int			pass_next_nodirs(t_e_ln_utils *e_ln_u)
{
	int i;

	e_ln_u->e_ln_last_b = e_ln_u->e_ln_last_a;
	e_ln_u->e_ln_old_b = e_ln_u->e_ln_old_a;
	i = 0;
	while (e_ln_u->e_ln_old_b->prev->edge == e_ln_u->e_ln_last_b->next->edge)
	{
		get_node_between_2_edge(e_ln_u->e_ln_last_b->edge,
		e_ln_u->e_ln_last_b->next->edge)->deja_vu = 0;
		e_ln_u->e_ln_last_b->edge->deja_vu = 0;
		e_ln_u->e_ln_last_b->edge->w1 = 1;
		e_ln_u->e_ln_last_b->edge->w2 = 1;
		e_ln_u->e_ln_last_b->edge->direction = BIDIR;
		e_ln_u->e_ln_last_b->next->edge->deja_vu = 0;
		e_ln_u->e_ln_last_b->next->edge->w1 = 1;
		e_ln_u->e_ln_last_b->next->edge->w2 = 1;
		e_ln_u->e_ln_last_b->next->edge->direction = BIDIR;
		e_ln_u->e_ln_last_b = e_ln_u->e_ln_last_b->next;
		e_ln_u->e_ln_old_b = e_ln_u->e_ln_old_b->prev;
		i++;
	}
	return (i);
}
