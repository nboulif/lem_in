/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:42:54 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 18:40:51 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_obj_part_two(t_objectif *obj)
{
	int		i;

	i = -1;
	while (++i < obj->best_sol.nb_way)
	{
		free(&obj->best_sol.way[i].nodes_lk[-1]);
		free(obj->best_sol.way[i].edges_lk);
	}
	free(obj->best_sol.way);
	i = -1;
	while (++i < obj->next_sol.nb_way)
	{
		free(obj->next_sol.way[i].nodes_lk);
		free(obj->next_sol.way[i].edges_lk);
	}
	free(obj->next_sol.way);
}

void		free_obj(t_objectif *obj)
{
	clock_t	time;

	time = clock();
	malloc_node_lk(0, 0);
	malloc_node(0, 0);
	free(obj->lst_node);
	free(obj->lst_node_lk);
	free(obj->lst_edge);
	free(obj->lst_edge_ord);
	free(obj->dists);
	free(obj->queue.node);
	free_obj_part_two(obj);
	fprintf(stderr, "free time -> %f\n", (float)(clock() - time) / C_P_S);
}

int			free_obj_and_print_error(t_objectif *obj, char *str)
{
	alloc_t_father(obj, 0);
	free_obj(obj);
	write(1, str, ft_strlen(str));
	return (0);
}
