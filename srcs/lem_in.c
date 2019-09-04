/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:42:54 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/04 21:20:42 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

int			read_all(char **str, int fd)
{
	int index;
	int size;
	int ret;

	size = SIZE_BUFF + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return (0);
	index = 0;
	while ((ret = read(fd, *str + index, SIZE_BUFF)) > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < SIZE_BUFF)
			return (index);
		if (index + SIZE_BUFF >= size - 1)
			if (!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
				return (0);
	}
	return (index);
}

void		estimate_max_way(t_objectif *obj)
{
	int				i;
	t_node_link		*link;

	obj->max_link = 0;
	i = -1;
	while (++i < obj->nb_node)
	{
		link = obj->lst_node_lk[i];
		while (link)
		{
			if (link->node->nb_edge_f > obj->max_link)
				obj->max_link = link->node->nb_edge_f;
			link = link->next;
		}
	}
	obj->max_way = ft_min(obj->start_node->nb_edge_f, obj->end_node->nb_edge_f,
						obj->max_link);
	obj->max_way = (obj->max_way < obj->nb_ants) ? obj->max_way : obj->nb_ants;
}

t_father	*alloc_t_father(t_objectif *obj, int mode)
{
	static t_father		*tab = NULL;
	static size_t		index = 0;

	if (!mode)
	{
		free(tab);
		return (NULL);
	}
	if (tab == NULL)
	{
		if (!(tab = malloc(sizeof(t_father) * (size_t)(obj->max_way + 1)
		* (size_t)(obj->nb_node + 1))))
			return (NULL);
	}
	index += (obj->max_way + 1);
	return (&tab[index - (obj->max_way + 1)]);
}

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

void		print_main_info(t_objectif obj)
{
	printf("nb_node => %d\n", obj.nb_node);
	printf("nb_edge => %d\n", obj.nb_edge);
	printf("nb_edge_f => %d\n", obj.nb_edge_f);
	printf("max_way => %d\n", obj.max_way);
}

void		free_node_lk(t_node_link *cur)
{
	if (cur->next)
		free_node_lk(cur->next);
	free(cur->node->edge);
	free(cur->node->name);
	free(cur->node);
	free(cur);
}

void		free_obj(t_objectif *obj)
{
	int i;

	i = -1;
	while (++i < obj->nb_node)
		if (obj->lst_node_lk[i])
			free_node_lk(obj->lst_node_lk[i]);
	free(obj->lst_node);
	free(obj->lst_node_lk);
	free(obj->lst_edge);
	free(obj->lst_edge_ord);
	free(obj->dists);
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

void		free_obj_and_print_error(t_objectif *obj, char *str)
{
	free_obj(obj);
	printf("%s\n", str);
}

void		lem_in(t_objectif *obj)
{
	if (!obj->max_way)
		return (free_obj_and_print_error(obj, "NO WAY AVAILABLE\n"));
	if (!(init_max_father_in_node(obj)))
		return (free_obj_and_print_error(obj, "Error init_max_father\n"));
	if (!init_solver(obj))
		return (free_obj_and_print_error(obj, "Error init solver\n"));
	if (!resolv(obj))
		return (free_obj_and_print_error(obj, "Error Resolv\n"));
	else
		print_ants(obj);
	alloc_t_father(obj, 0);
	free_obj(obj);
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
	if (!(size = read_all(&str, fd)) ||
		!extract_info(&obj, str) || !init_resolv(&obj))
	{
		free_obj(&obj);
		printf("Error init\n");
		return (0);
	}
	estimate_max_way(&obj);
	print_node_and_edge(str, size);
	lem_in(&obj);
	return (1);
}
