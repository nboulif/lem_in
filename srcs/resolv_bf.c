/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_bf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/04 20:55:31 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int		check_atomic(t_objectif *obj, t_way *way)
{
	t_edge_link		*e_check;
	int				z;
	t_edge_link		*e_ln;
	t_node			*node;
	t_node			*node_checker;

	e_ln = &way->edges_lk[0];
	node = obj->start_node;
	while (e_ln)
	{
		node = get_right_node_in_edge(e_ln->edge, node, 0);
		if (e_ln->next && !node)
			return (printf("DISCONTINUE\n"));
		if (node)
		{
			z = -1;
			while (++z < obj->next_sol.nb_way)
			{
				e_check = obj->next_sol.way[z].edges_lk;
				node_checker = obj->start_node;
				while (e_check)
				{
					node_checker = get_right_node_in_edge(e_check->edge, node_checker, 0);
					if (node_checker == node && node != obj->end_node && node)
						return (printf("CROISEMENT\n"));
					e_check = e_check->next;
				}
			}
		}
		e_ln = e_ln->next;
	}
	return (0);
}

int		find_way(t_objectif *obj)
{
	int			i;

	if (!(init_way(obj, &obj->next_sol.way[obj->next_sol.nb_way])))
		return (-1);
	i = 0;
	while (i < obj->nb_node)
		obj->lst_node[i++]->deja_vu_in_way = 0;
	if (!apply_algo_bellman_ford(obj))
	{
		free(obj->next_sol.way[obj->next_sol.nb_way].nodes_lk);
		free(obj->next_sol.way[obj->next_sol.nb_way].edges_lk);
		return (0);
	}
	make_way(obj, &obj->next_sol);
	merge_way(&obj->next_sol);
	if (check_atomic(obj, &obj->next_sol.way[obj->next_sol.nb_way]))
	{
		printf("ERROR\n");
		return (0);
	}
	return (1);
}
