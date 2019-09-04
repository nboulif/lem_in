/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:03:31 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void create_node_tab(t_objectif *obj, t_solution *sol)
{
	t_node *current;
	int i;
	int x;
	t_edge_link *e_ln;

	x = -1;
	while (++x < sol->nb_way)
	{
		i = 0;
		current = obj->start_node;
		sol->way[x].nodes_lk[0].node = current;
		e_ln = sol->way[x].edges_lk;
		while (1)
		{
			current = get_right_node_in_edge(e_ln->edge, current, 0);

			if (!current)
				break;
			sol->way[x].nodes_lk[i + 1].node = current;
			sol->way[x].nodes_lk[i].next = &sol->way[x].nodes_lk[i + 1];
			e_ln = e_ln->next;
			if (current->name == obj->end_node->name)
			{
				sol->way[x].nodes_lk[i + 1].next = NULL;
				break;
			}
			i++;
		}
		sol->way[x].nodes_lk = sol->way[x].nodes_lk->next;
	}
}

void evaluate_turn_solution(t_objectif *obj, t_solution *sol)
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
			break;
	}
	sol->nb_turn = sum / i +
				   nb_ants / i +
				   !!(nb_ants % i);
}

int init_solver(t_objectif *obj, t_solution *best_sol, t_solution *next_sol)
{
	*best_sol = (t_solution){NULL, 0, 0, 0};
	obj->max_way++;
	if (!(best_sol->way = (t_way *)malloc(sizeof(t_way) * obj->max_way)))
		return (0);
	*next_sol = (t_solution){NULL, 0, 0, 0};
	if (!(next_sol->way = (t_way *)malloc(sizeof(t_way) * obj->max_way)))
	{
		free(best_sol->way);
		return (0);
	}
	best_sol->nb_way = 0;
	next_sol->nb_way = 0;
	if (!(obj->dists = (int *)malloc(sizeof(int) * ((obj->nb_node * 2) + 1))))
	{
		free(next_sol->way);
		free(best_sol->way);
		return (0);
	}
	return (1);
}

int resolv(t_objectif *obj)
{
	int res;
	int i;
	t_solution best_sol;
	t_solution next_sol;

	init_solver(obj, &best_sol, &next_sol);

	i = 0;
	best_sol.nb_turn = INT_MAX;
	while (i++ < obj->max_way)
	{
		res = find_way(obj, &next_sol);
		if (!(res))
		{
			printf("NO MORE WAY\n");
			break;
		}
		else if (res == -1)
		{
			printf("ERROR RESOLV\n");
			return (-1);
		}
		++next_sol.nb_way;
		evaluate_turn_solution(obj, &next_sol);
		if (best_sol.nb_way && best_sol.nb_turn < next_sol.nb_turn)
		{
			printf("MORE TURN\n");
			//break ;
			continue;
		}
		for (int i = best_sol.nb_way; i < next_sol.nb_way; i++)
			if (!init_way(obj, &best_sol.way[i]))
				return (0);
		//****** faire une fonction **********
		for (int x = 0; x < next_sol.nb_way; x++)
		{
			t_edge_link *edges_lk = next_sol.way[x].edges_lk;
			int y = 0;

			while (edges_lk)
			{
				best_sol.way[x].edges_lk[y].edge = edges_lk->edge;
				best_sol.way[x].edges_lk[y].next = NULL;
				if ((edges_lk = edges_lk->next))
					best_sol.way[x].edges_lk[y].next = &best_sol.way[x].edges_lk[y + 1];
				y++;
			}
			best_sol.way[x].len = next_sol.way[x].len;
		}
		best_sol.nb_way = next_sol.nb_way;
		best_sol.nb_turn = next_sol.nb_turn;
		best_sol.len = next_sol.len;
		//****** ****************** **********
		if (best_sol.nb_way == obj->nb_ants)
			break;
	}
	if (best_sol.nb_way)
	{
		create_node_tab(obj, &best_sol);
		print_ants(obj, &best_sol);
		for (int i = 0; i < best_sol.nb_way; i++)
		{
			free(&best_sol.way[i].nodes_lk[-1]);
			free(best_sol.way[i].edges_lk);
		}
		free(best_sol.way);
		for (int i = 0; i < next_sol.nb_way; i++)
		{
			free(next_sol.way[i].nodes_lk);
			free(next_sol.way[i].edges_lk);
		}
		free(next_sol.way);
		return (1);
	}
	return (0);
}
