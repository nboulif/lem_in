/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:34:40 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
