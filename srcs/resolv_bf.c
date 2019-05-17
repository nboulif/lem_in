/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_bf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:29:24 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 		check_atomic(t_objectif *obj, t_solution *sol, t_way *way)
{
	t_edge_link		*e_check;
	int 			z;
	
	t_edge_link 	*e_ln;
	t_node			*node;
	int 			check;
	
	check = 1;
	printf("len => %d\n", way->len);

	e_ln = &way->edges_lk[0];
	node = obj->start_node;
	while (e_ln)
	{
		node = get_right_node_in_edge(e_ln->edge, node, 0);

		if (e_ln->next && !node)
		{
			printf("DISCONTINUE\n");
			return (0);
		}
		if (node)
		{
			z = -1;
			while(++z < sol->nb_way)
			{
				e_check = sol->way[z].edges_lk;
				t_node *node_checker = obj->start_node;
				while (e_check)
				{
					node_checker = get_right_node_in_edge(e_check->edge, node_checker, 0);
					if (node_checker == node && node != obj->end_node && node)
					{	

						printf("CROISEMENT  way  %d & %d   |%s|-|%s|  |%s|-|%s|\n",
							sol->nb_way, z, 
							e_ln->edge->node1->name, e_ln->edge->node2->name, e_check->edge->node1->name, e_check->edge->node2->name
						);
						printf("node dv		|%d|-|%d| & |%d|-|%d|\n", e_ln->edge->node1->deja_vu, e_ln->edge->node2->deja_vu, e_check->edge->node1->deja_vu, e_check->edge->node2->deja_vu);
						printf("weight		|%d|-|%d| & |%d|-|%d|\n", e_ln->edge->w1, e_check->edge->w2, e_ln->edge->w1, e_check->edge->w2);
						printf("dir				 |%d| & |%d|\n", e_ln->edge->direction, e_check->edge->direction);
						printf("edge dv			 |%d| & |%d|\n", e_ln->edge->deja_vu, e_check->edge->deja_vu);
						check = 0;
					}
					e_check = e_check->next;
				}
			}
		
		}
		e_ln = e_ln->next;
	}
	
	return (check);
}

int 		find_way(t_objectif *obj, t_solution *sol)
{ 
	t_way 		*way;

	way = &sol->way[sol->nb_way];

	if (!(init_way(obj, way)))
	    return (-1);


	int i;
	i = 0;
	while (i < obj->nb_node)
		obj->lst_node[i++]->deja_vu_in_way = 0;

	if (!apply_algo_bellman_ford(obj, sol))
		return(0);


	printf("cost => %d\n", way->cost);

	make_way(obj, sol);
	printf("make way ok\n");
	print_way_status_before_merge(way);
	printf("print before ok\n");
	merge_way(sol);
	printf("merge ok\n");

	int check;
	check = check_atomic(obj, sol, way);
	if (!check)
	{
		printf("\n\nCROSSSSSSSSSSSSSSSSSSING\n\n");	
		return (check);
	}
	print_way_status_after_merge(obj, way);
	return (check);
	
}
