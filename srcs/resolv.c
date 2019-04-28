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

void 		make_way(t_objectif *obj, t_solution *sol)
{
	t_node	*node;
	t_tube	*l_tube;
	int		x;
	int		i;

	x = -1;
	i = -1;
	node = obj->end_node;
	sol->way[sol->nb_way - 1].len = 0;
	while (node != obj->start_node)
	{
		sol->way[sol->nb_way - 1].node[sol->way[sol->nb_way - 1].len] = node;
		sol->way[sol->nb_way - 1].tube[sol->way[sol->nb_way - 1].len++] = node->father_tube[0];
		//node->nb_of_inway = 0;
		l_tube = node->father_tube[0];
		if (node->name == node->father_tube[0]->node1->name)
		{
			node->father_tube[0]->direction -= UNIDIR1;
			node->father_tube[0]->w2 = -1;
			node = node->father_tube[0]->node2;
		}
		else
		{
			node->father_tube[0]->direction -= UNIDIR2;
			node->father_tube[0]->w1 = -1;
			node = node->father_tube[0]->node1;
		}
		node->in_a_way = l_tube;
		node->nb_of_inway = sol->nb_way;
	}
}

int		resolv(t_objectif *obj)
{
	t_solution	best_sol;
	t_solution	next_sol;

	best_sol = (t_solution){NULL, 0, 0, 0};

    if (//!(first_way(obj, &first))
		!(next_sol = find_way_bf(obj, best_sol)).way)
			return (-1);
			// exit(printf("ERROR\n"));

	printf("%d\n", best_sol.nb_way);

	print_way(obj, best_sol);

	return (1);
}