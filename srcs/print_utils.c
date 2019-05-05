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



void check(t_objectif *obj, t_solution *sol, t_node *node, int x)
{
	t_edge_link		*e_check;
	int 			z;

	z = x;
	while(++z < sol->nb_way)
	{
		e_check = sol->way[z].edges_lk;
		t_node *node_checker = obj->start_node;
		while (e_check)
		{
			node_checker = get_right_node_in_edge(e_check->edge, node_checker, 0);
			if (node_checker == node && node != obj->end_node && node)
				printf("CROISEMENT way %d&%d : |%s|\n", x, z, node->name);
			e_check = e_check->next;
		}
	}

}


void 			print_way(t_objectif *obj, t_solution *sol)
{
	int 		i;
	int 		x;
	// t_node_link		*n_ln;
	t_edge_link		*e_ln;

	printf("\n\nend node name => |%s|\n", obj->end_node->name);
	printf("nb way => |%d|\n\n", sol->nb_way);

	t_node		*node;

	x = -1;
	while (++x < sol->nb_way)
	{
		printf("chemin %d\n", x);
		i = 0;
		// n_ln = &obj->sol->way[x].nodes_lk[0];
		e_ln = &sol->way[x].edges_lk[0];
		node = obj->start_node;
		while (e_ln)
		{
			
			printf("%d. ", i);
			node = get_right_node_in_edge(e_ln->edge, node, 0);
			if (node) 
			{
				printf("|%s|", node->name);
				printf(" |%s|-|%s|\n", 
					e_ln->edge->node1->name, 
					e_ln->edge->node2->name
				);
			}
			if (node)
				check(obj, sol, node, x);
			
			if (e_ln->next && !get_right_node_in_edge(e_ln->next->edge, node, 0))
				printf("DISCONTINUE\n");

			i++;
			// n_ln = n_ln->next;
			e_ln = e_ln->next;
		}	
		printf("\n");
	}


}
