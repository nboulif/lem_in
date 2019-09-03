/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:05:01 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/22 17:05:02 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int			init_node(t_node *node, char *name, int nb_node, int size_name)
{
	node->name = name;
	node->id = hash((unsigned char*)name) % nb_node;
	node->nb_edge_o = 0;
	node->nb_edge_f = 0;
	node->edge = NULL;
	node->range = 0;
	// if (!(node->father_node = malloc(sizeof(t_node*))) ||
	// 	!(node->father_edge = malloc(sizeof(t_edge*))))
	// 	return (0);
	// ft_memset(node->father_node, 0, 1 * sizeof(t_node*));
	// ft_memset(node->father_edge, 0, 1 * sizeof(t_edge*));
	node->nb_father_n = 1;
	node->nb_father_t = 1;
	node->i_nb_father = 0;
	node->in_a_way = NULL;
	node->deja_vu = 0;
	node->deja_vu_init = 0;
	node->nb_of_inway = -1;
	node->size_name = size_name;
	return (1);
}

t_node		*create_node(char *str, int *i, int nb_node)
{
	t_node	*node;
	char	*name;
	int		index;
	int		size;

	size = 21;
	index = 0;
	if (str[*i] == 'L' || !(name = malloc(size)))
		return (NULL);
	while (str[*i] != ' ')
	{
		if (index == size - 1)
			if (!ft_realloc((void**)&name, &size, size * 2, sizeof(char)))
			{
				free(name);
				return (NULL);
			}
		name[index++] = str[(*i)++];
	}
	name[index++] = 0;
	if (!(node = malloc(sizeof(t_node))) ||
		!ft_realloc((void**)&name, &index, index, sizeof(char)) ||
		!init_node(node, name, nb_node, index))
	{
		free(name);
		free(node);
		return (NULL);
	}
	
	zap_line(str, i);
	return (node);
}

int			add_in_lst(t_node_link **link, t_node *node)
{
	t_node_link	*lk;

	if (!(lk = malloc(sizeof(t_node))))
	 	return (0);
	lk->next = *link;
	lk->node = node;
	*link = lk;
	return (1);
}

int			exec_command(t_objectif *obj, char *str, int *i)
{
	t_node		*node;
	int			go;

	go = 0;
	while (1)
	{
		if (!ft_strncmp(str + *i, "##start\n", 8))
			go = 8;
		else if (!ft_strncmp(str + *i, "##end\n", 6))
			go = 6;
		go ? zap_comm(str, i) : zap_line(str, i);
		if (go || str[*i] != '#')
			break ;
	}
	node = NULL;
	if (go && ((go == 8 && obj->start_node) || (go == 6 && obj->end_node) ||
		(!(node = create_node(str, i, obj->nb_node)) ||
		!add_in_lst(&obj->lst_node_lk[node->id], node))))
		return (0);
	if (go == 8)
		obj->start_node = node;
	else if (go == 6)
		obj->end_node = node;
	return (1);
}

int			make_tab_node(t_objectif *obj, char *str, int *i)
{
	t_node	*node;
	int		x;

	x = 0;
	if (!(obj->lst_node_lk = malloc(sizeof(t_node_link*)
		* obj->nb_node)))
		return (0);
	while (x < obj->nb_node)
		obj->lst_node_lk[x++] = NULL;
	while (((char*)(unsigned long)*i)[(long)str] == '#' ||
			is_node_cond(str, i))
	{
		if (str[*i] == '#')
		{
			if (!(exec_command(obj, str, i)))
				return (0);
		}
		else
		{
			if (!(node = create_node(str, i, obj->nb_node)) ||
				!add_in_lst(obj->lst_node_lk + node->id, node))
				return (0);
		}
	}
	return (1);
}
