/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:20:39 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			create_node_tab_part_two(t_objectif *obj, int x, int *i,
		t_edge_link *e_ln)
{
	t_node		*current;

	current = obj->start_node;
	while (1)
	{
		current = get_right_node_in_edge(e_ln->edge, current, 0);
		if (!current)
			break ;
		obj->best_sol.way[x].nodes_lk[(*i) + 1].node = current;
		obj->best_sol.way[x].nodes_lk[(*i)].next =
			&obj->best_sol.way[x].nodes_lk[(*i) + 1];
		e_ln = e_ln->next;
		if (current->name == obj->end_node->name)
		{
			obj->best_sol.way[x].nodes_lk[(*i) + 1].next = NULL;
			break ;
		}
		(*i)++;
	}
}

void			create_node_tab(t_objectif *obj)
{
	int			i;
	int			x;
	t_edge_link	*e_ln;

	x = -1;
	while (++x < obj->best_sol.nb_way)
	{
		i = 0;
		obj->best_sol.way[x].nodes_lk[0].node = obj->start_node;
		e_ln = obj->best_sol.way[x].edges_lk;
		create_node_tab_part_two(obj, x, &i, e_ln);
		obj->best_sol.way[x].nodes_lk = obj->best_sol.way[x].nodes_lk->next;
	}
}

void			print_node_and_edge(char *str, int size)
{
	write(1, str, size);
	if (str[size - 1] != '\n')
		ft_putchar('\n');
	ft_putchar('\n');
}

int				free_output_error(t_solution *sol, t_string **output, int i)
{
	while (i < sol->nb_turn + 1)
		free(output[0][i++].chaine);
	free(*output);
	return (0);
}
