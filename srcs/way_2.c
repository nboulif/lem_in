/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:34:36 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		merge_edge_part_two(t_solution *sol, t_e_ln_utils *e_ln_u,
	t_node *node_in, t_node *node_out)
{
	if (node_in->deja_vu_in_way > 1 && !(node_in->deja_vu_in_way % 2))
		node_in->deja_vu_in_way += 1;
	else
	{
		e_ln_u->e_ln_last_b = e_ln_u->e_ln_last_a;
		e_ln_u->e_ln_old_b = e_ln_u->e_ln_last_a;
		merge_multiple_disc_edge(sol, e_ln_u);
		node_out->deja_vu_in_way -= 3;
	}
}

int			merge_multiple_edge(t_solution *sol, t_e_ln_utils *e_ln_u)
{
	int			i;
	t_node		*node_in;
	t_node		*node_out;

	node_in = get_node_between_2_edge(e_ln_u->e_ln_last_a->edge,
		e_ln_u->e_ln_last_a->prev->edge);
	i = pass_next_nodirs(e_ln_u);
	node_out = get_node_between_2_edge(e_ln_u->e_ln_last_b->edge,
		e_ln_u->e_ln_last_b->next->edge);
	if (node_in->deja_vu_in_way > 1 || node_out->deja_vu_in_way > 1)
		merge_edge_part_two(sol, e_ln_u, node_in, node_out);
	else
	{
		e_ln_u->e_ln_old_a->next->prev = e_ln_u->e_ln_last_a->prev;
		e_ln_u->e_ln_old_b->prev->next = e_ln_u->e_ln_last_b->next;
		e_ln_u->e_ln_last_a->prev->next = e_ln_u->e_ln_old_a->next;
		e_ln_u->e_ln_last_b->next->prev = e_ln_u->e_ln_old_b->prev;
	}
	return (i);
}

void		merge_one_edge(t_solution *sol, t_e_ln_utils *e_ln_u)
{
	t_node *node_in;
	t_node *node_out;

	if (e_ln_u->e_ln_last_a->edge->node1->deja_vu_in_way > 1
		|| e_ln_u->e_ln_last_a->edge->node2->deja_vu_in_way > 1)
	{
		node_in = get_node_between_2_edge(e_ln_u->e_ln_last_a->edge,
			e_ln_u->e_ln_last_a->prev->edge);
		node_out = get_right_node_in_edge(e_ln_u->e_ln_last_a->edge,
			node_in, 0);
		merge_edge_part_two(sol, e_ln_u, node_in, node_out);
	}
	else
	{
		e_ln_u->e_ln_old_a->next->prev = e_ln_u->e_ln_last_a->prev;
		e_ln_u->e_ln_old_a->prev->next = e_ln_u->e_ln_last_a->next;
		e_ln_u->e_ln_last_a->prev->next = e_ln_u->e_ln_old_a->next;
		e_ln_u->e_ln_last_a->next->prev = e_ln_u->e_ln_old_a->prev;
	}
}
