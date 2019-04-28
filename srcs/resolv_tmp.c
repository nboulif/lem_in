/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_tmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:33:02 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:33:03 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			add_linked_node_in_queue(t_objectif *obj, t_node *node, t_queue *queue, int range)
{
	int		i;
	t_node	*next;

	i = -1;
	while (++i < node->nb_tube_f)
	{
		next = get_right_node_in_tube(node, i);

		if (!next->father_node[0])
		{
			if (!(check_need_realloc(next))) 
				return (0);
			next->father_node[0] = node;
			next->father_tube[0] = node->tube[i];

			next->range = range;

			queue->node[queue->size_queue++ % obj->nb_node] = next;

		}
		if (next == obj->end_node)
			return (1);
	}
	return (2);
}

int 		first_way(t_objectif *obj, t_solution *sol)
{
    t_queue     queue;
	t_node		*current;
	int			range;
	int			finish;

	current = obj->start_node;
	range = 1;
	queue = (t_queue){NULL, 0, 0};
	if (!init_solution(obj, sol, &queue))
		return (0);
	while (1)
	{
		add_linked_node_in_queue(obj, current, &queue, range++);
		if (queue.index == queue.size_queue)
			break ;
		current = queue.node[queue.index % obj->nb_node];
		queue.node[queue.index++ % obj->nb_node] = NULL;
	}
	
	finish = 1;

	if (!finish && obj->end_node->father_node[0])
	{
		finish = 1;
		make_way(obj, sol);
	}
	if (finish)
		return (1);
	return (0);
}

int		find_way(t_objectif *obj, t_solution *sol)
{
	if (!(first_way(obj, sol)))
		exit(printf("ERROR\n"));
	printf("%d\n", sol->way[0].len);

	return (1);
}