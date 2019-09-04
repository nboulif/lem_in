/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/04 20:36:45 by nboulif          ###   ########.fr       */
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

void		merge_edge_part_two(t_solution *sol, t_e_ln_utils *e_ln_u,
	t_node *node_in, t_node *node_out)
{
	if (node_in->deja_vu_in_way > 1 && !(node_in->deja_vu_in_way % 2))
		node_in->deja_vu_in_way += 1;
	else
	{
		printf("SPECIAL MERGE ONE 2\n");
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

void		merge_way_part_two(t_solution *sol, int *i,
				int *finish, t_e_ln_utils *e_ln_u)
{
	int z;

	z = sol->nb_way;
	while (z-- > 0)
	{
		e_ln_u->e_ln_old_a = sol->way[z].edges_lk;
		while (e_ln_u->e_ln_old_a &&
			(e_ln_u->e_ln_old_a->edge != e_ln_u->e_ln_last_a->edge))
			e_ln_u->e_ln_old_a = e_ln_u->e_ln_old_a->next;
		if (e_ln_u->e_ln_old_a
			&& (e_ln_u->e_ln_old_a->edge == e_ln_u->e_ln_last_a->edge))
		{
			*finish = 0;
			if (e_ln_u->e_ln_last_a->next && e_ln_u->e_ln_old_a->prev &&
			e_ln_u->e_ln_old_a->prev->edge == e_ln_u->e_ln_last_a->next->edge)
				*i += merge_multiple_edge(sol, e_ln_u);
			else
				merge_one_edge(sol, e_ln_u);
			break ;
		}
	}
}

void		merge_way(t_solution *sol)
{
	int				i;
	int				finish;
	t_e_ln_utils	e_ln_u;

	while (1)
	{
		finish = 1;
		i = -1;
		while (++i < sol->way[sol->nb_way].len)
		{
			e_ln_u.e_ln_last_a = &sol->way[sol->nb_way].edges_lk[i];
			if (e_ln_u.e_ln_last_a->edge &&
				e_ln_u.e_ln_last_a->edge->direction == NODIR)
				merge_way_part_two(sol, &i, &finish, &e_ln_u);
		}
		if (finish)
			break ;
	}
	update_ways_len_with_node_lk(sol);
}

void		init_make_way(t_objectif *obj, t_solution *sol, t_make_way_utils *u)
{
	u->way = &sol->way[sol->nb_way];
	set_way_len_with_fathers(sol, obj->end_node);
	u->i = u->way->len - 1;
	u->way->nodes_lk[u->i].node = obj->end_node;
	u->way->nodes_lk[u->i].next = NULL;
	u->mode = obj->end_node->father_mode;
}

void		make_way_part_two(t_objectif *obj, t_solution *sol,
	t_make_way_utils *u)
{
	if (u->i > 0)
		u->way->nodes_lk[u->i - 1].node = !u->mode ?
		u->n_ln->node->fathers[sol->nb_way].node :
		u->n_ln->node->fathers[sol->nb_way].node_out;
	u->mode = !u->mode ? u->n_ln->node->father_mode : 0;
	if (u->i > 0)
	{
		u->way->nodes_lk[u->i - 1].next = u->n_ln;
		if (u->way->nodes_lk[u->i - 1].node->id != obj->start_node->id &&
			u->way->nodes_lk[u->i - 1].node->id != obj->end_node->id)
		{
			u->way->nodes_lk[u->i - 1].node->deja_vu += 1;
			u->way->nodes_lk[u->i - 1].node->deja_vu_in_way += 1;
		}
	}
	u->e = u->e_ln->edge;
	u->dir = u->e->node1->id == u->n_ln->node->id ? UNIDIR2 : UNIDIR1;
	u->w = u->e->node1->id == u->n_ln->node->id ? &u->e->w1 : &u->e->w2;
	u->e->direction == BIDIR ? *u->w = -(*u->w) : 0;
	u->e->direction -= u->dir;
	--u->i;
}

int			make_way(t_objectif *obj, t_solution *sol)
{
	t_make_way_utils	u;

	init_make_way(obj, sol, &u);
	while (u.i + 1)
	{
		u.n_ln = &u.way->nodes_lk[u.i];
		u.e_ln = &u.way->edges_lk[u.i];
		if (!u.mode)
			u.e_ln->edge = u.n_ln->node->fathers[sol->nb_way].edge;
		else
			u.e_ln->edge = u.n_ln->node->fathers[sol->nb_way].edge_out;
		u.e_ln->edge->deja_vu += 1;
		u.e_ln->next = u.n_ln->node == obj->end_node ? NULL :
			&u.way->edges_lk[u.i + 1];
		u.e_ln->prev = u.i == 0 ? NULL : &u.way->edges_lk[u.i - 1];
		make_way_part_two(obj, sol, &u);
	}
	return (1);
}
