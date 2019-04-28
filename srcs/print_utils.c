/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 04:02:54 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 04:02:55 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_all_tube(t_objectif *obj)
{
	int			i;
	int			x;
	t_node_link	*link;

	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			printf("link->name |%s|\n", link->node->name);
			x = -1;
			while (++x < link->node->nb_tube_f)
				printf("|%s|-|%s|\n", link->node->tube[x]->node1->name,
									link->node->tube[x]->node2->name);
			printf("\n");
			sleep(1);
			link = link->next;
		}
	}
}

void 			print_way(t_objectif *obj, t_solution best)
{
	int 		i;
	int 		x = -1;

	printf("end node name |%s|\n", obj->end_node->name);
	while (++x < best.nb_way)
	{
		printf("chemin %d\n", x);
		i = 0;
		while (1)
		{
			printf("%d. |%s|", i, best.way[x].node[i]->name);
			printf(" |%s|-|%s|\n", best.way[x].tube[i]->node1->name, best.way[x].tube[i]->node2->name);
			if (best.way[x].node[i++] == obj->end_node)
				break ;
		}
		printf("\n");
	}
}