/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:42:54 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 18:41:51 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			init_max_father_in_node(t_objectif *obj)
{
	int		i;
	int		x;
	t_node	*node;

	i = -1;
	while (++i < obj->nb_node)
	{
		node = obj->lst_node[i];
		if (node->nb_edge_f == 1 &&
			node != obj->start_node &&
			node != obj->end_node)
		{
			if (node == node->edge[0]->node2)
				delete_this_edge(node->edge[0]->node1, node->edge[0], obj);
			else
				delete_this_edge(node->edge[0]->node2, node->edge[0], obj);
			continue;
		}
		if (!(node->fathers = alloc_t_father(obj, 1)))
			return (0);
		x = 0;
		while (x < (obj->max_way + 1))
			node->fathers[x++] = (t_father){NULL, NULL, NULL, NULL, 0};
	}
	return (1);
}

int			lem_in(t_objectif *obj, char *str, int size)
{
	if (!obj->max_way)
		return (free_obj_and_print_error(obj, "ERROR\n"));
	if (!(init_max_father_in_node(obj)))
		return (free_obj_and_print_error(obj, "ERROR\n"));
	if (!init_solver(obj))
		return (free_obj_and_print_error(obj, "ERROR\n"));
	if (!resolv(obj))
		return (free_obj_and_print_error(obj, "ERROR\n"));
	else
	{
		print_node_and_edge(str, size);
		if (!print_ants(obj))
			return (free_obj_and_print_error(obj, "ERROR\n"));
	}
	alloc_t_father(obj, 0);
	free_obj(obj);
	return (1);
}

int			main(int argc, char **argv)
{
	int			fd;
	char		*str;
	t_objectif	obj;
	int			size;

	fd = 0;
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			fd = 0;
	}
	ft_memset(&obj, 0, sizeof(t_objectif));
	str = NULL;
	if (!(size = read_all(&str, fd)) || !extract_info(&obj, str)
		|| !init_resolv(&obj))
	{
		free(str);
		free_obj_and_print_error(&obj, "ERROR\n");
		return (0);
	}
	estimate_max_way(&obj);
	lem_in(&obj, str, size);
	free(str);
	return (1);
}
