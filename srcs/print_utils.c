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

void 			print_node_and_edge(char *str, int size)
{
	write(1, str, size - 1);
	if (str[size - 2] != '\n')
		ft_putchar('\n');
	free(str);
	ft_putchar('\n');
}

void			print_all_edge(t_objectif *obj)
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
			while (++x < link->node->nb_edge_f)
				printf("|%s|-|%s|\n", link->node->edge[x]->node1->name,
									link->node->edge[x]->node2->name);
			printf("\n");
			sleep(1);
			link = link->next;
		}
	}
}

void 			print_way(t_objectif *obj)
{
	int 		i;
	int 		x;
	// t_node_link		*n_ln;
	t_edge_link		*e_ln;

	printf("\n\nend node name => |%s|\n", obj->end_node->name);
	printf("nb way => |%d|\n\n", obj->sol->nb_way);


	x = -1;
	while (++x < obj->sol->nb_way)
	{
		printf("chemin %d\n", x);
		i = 0;
		// n_ln = &obj->sol->way[x].nodes_lk[0];
		e_ln = &obj->sol->way[x].edges_lk[0];
		while (e_ln)
		{

			printf("%d. ", i);
			// printf("|%s|", n_ln->node->name);
			printf(" |%s|-|%s|\n", 
				e_ln->edge->node1->name, 
				e_ln->edge->node2->name
			);
			i++;
			// n_ln = n_ln->next;
			e_ln = e_ln->next;
		}	
		printf("\n");
	}


}