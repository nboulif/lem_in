/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:41:00 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		evaluate_turn_solution(t_objectif *obj, t_solution *sol)
{
	int i;
	int sum;
	int nb_ants;

	sum = 0;
	i = 0;
	while (i < sol->nb_way)
		sum += sol->way[i++].len;
	nb_ants = obj->nb_ants - i;
	while (sum % i)
	{
		sum++;
		if (--nb_ants == 0)
			break ;
	}
	sol->nb_turn = sum / i + nb_ants / i + !!(nb_ants % i);
}

int			init_solver(t_objectif *obj)
{
	obj->best_sol = (t_solution){NULL, 0, 0, 0};
	obj->max_way++;
	if (!(obj->best_sol.way = (t_way *)malloc(sizeof(t_way) * obj->max_way)))
		return (0);
	obj->next_sol = (t_solution){NULL, 0, 0, 0};
	if (!(obj->next_sol.way = (t_way *)malloc(sizeof(t_way) * obj->max_way)))
	{
		free(obj->best_sol.way);
		return (0);
	}
	obj->best_sol.nb_way = 0;
	obj->next_sol.nb_way = 0;
	if (!(obj->dists = (int *)malloc(sizeof(int) * ((obj->nb_node * 2) + 1))))
	{
		free(obj->next_sol.way);
		free(obj->best_sol.way);
		return (0);
	}
	obj->best_sol.nb_turn = INT_MAX;
	return (1);
}

void		next_to_best_sol(t_solution *best_sol, t_solution *next_sol)
{
	t_edge_link	*edges_lk;
	int			y;
	int			x;

	x = -1;
	while (++x < next_sol->nb_way)
	{
		edges_lk = next_sol->way[x].edges_lk;
		y = 0;
		while (edges_lk)
		{
			best_sol->way[x].edges_lk[y].edge = edges_lk->edge;
			best_sol->way[x].edges_lk[y].next = NULL;
			if ((edges_lk = edges_lk->next))
				best_sol->way[x].edges_lk[y].next =
					&best_sol->way[x].edges_lk[y + 1];
			y++;
		}
		best_sol->way[x].len = next_sol->way[x].len;
	}
	best_sol->nb_way = next_sol->nb_way;
	best_sol->nb_turn = next_sol->nb_turn;
	best_sol->len = next_sol->len;
}

int			resolv_part_init(t_objectif *obj, t_resolv_utils *u)
{
	if (!(obj->queue.node = malloc(sizeof(t_node*) * (obj->nb_node * 2))))
		return (0);
	obj->queue.node[0] = obj->start_node;
	obj->queue.size_queue = 1;
	obj->queue.index = 0;
	u->time = clock();
	u->i = 0;
	return (1);
}

int			resolv(t_objectif *obj)
{
	t_resolv_utils u;

	if (!(resolv_part_init(obj, &u)))
		return (0);
	while (u.i++ < obj->max_way)
	{
		if (!(u.res = find_way(obj)))
			break ;
		else if (u.res == -1)
			return (0);
		++obj->next_sol.nb_way;
		evaluate_turn_solution(obj, &obj->next_sol);
		if (obj->best_sol.nb_way &&
				obj->best_sol.nb_turn < obj->next_sol.nb_turn)
			continue;
		u.y = obj->best_sol.nb_way;
		while (u.y < obj->next_sol.nb_way)
			if (!init_way(obj, &obj->best_sol.way[u.y++]))
				return (0);
		next_to_best_sol(&obj->best_sol, &obj->next_sol);
		if (obj->best_sol.nb_way == obj->nb_ants)
			break ;
	}
	fprintf(stderr, "resolv time -> |%f|\n", (float)(clock() - u.time) / C_P_S);
	return (obj->best_sol.nb_way ? 1 : 0);
}
