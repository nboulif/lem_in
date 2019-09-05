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

t_node		*malloc_node(int nb_node, int mode)
{
	static t_node	*node_malloc = NULL;
	static int		index = 0;
	int				i;

	if (!mode)
	{
		i = 0;
		while (i < index)
		{
			free(node_malloc[i].edge);
			free(node_malloc[i++].name);
		}
		free(node_malloc);
		return (NULL);
	}
	if (!node_malloc)
		if (!(node_malloc = malloc(sizeof(t_node) * nb_node)))
			return (NULL);
	return (&node_malloc[index++]);
}

t_node		*create_node(char *str, int *i, int nb_node)
{
	t_node		*node;
	t_string	nm;

	nm.size = 21;
	nm.index = 0;
	if (str[*i] == 'L' || !(nm.chaine = malloc(nm.size)))
		return (NULL);
	while (str[*i] != ' ')
	{
		if (nm.index == nm.size - 1 &&
		!ft_realloc((void**)&nm.chaine, &nm.size, nm.size * 1.8, sizeof(char)))
				return (NULL);
		nm.chaine[nm.index++] = str[(*i)++];
	}
	if (!(node = malloc_node(nb_node, 1)) ||
		(nm.index != nm.size &&
		!ft_realloc((void**)&nm.chaine, &nm.index, nm.index, sizeof(char))) ||
		!init_node(node, nm.chaine, nb_node, nm.index))
	{
		free(nm.chaine);
		free(node);
		return (NULL);
	}
	zap_line(str, i);
	return (node);
}

t_node_link	*malloc_node_lk(int nb_node, int mode)
{
	static t_node_link	*node_lk_malloc = NULL;
	static int		index = 0;
	int				i;

	if (!mode)
	{
		i = 0;
		free(node_lk_malloc);
		return (NULL);
	}
	if (!node_lk_malloc)
		if (!(node_lk_malloc = malloc(sizeof(t_node_link) * (nb_node + 1))))
			return (NULL);
	return (&node_lk_malloc[index++]);
}

int			add_in_lst(t_node_link **link, t_node *node, int nb_node)
{
	t_node_link	*lk;

	if (!(lk = malloc_node_lk(nb_node, 1)))
		// !(lk = malloc(sizeof(t_node_link))))
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
	node = NULL;
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
	if (go && ((go == 8 && obj->start_node) ||
		 (go == 6 && obj->end_node) ||
		 (!(node = create_node(str, i, obj->nb_node)) ||
		 !add_in_lst(&obj->lst_node_lk[node->id], node, obj->nb_node))))
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

	if (!(obj->lst_node_lk = malloc(sizeof(t_node_link*) *
			obj->nb_node)))
		return (0);
	ft_memset(obj->lst_node_lk, 0, sizeof(t_node_link*) * obj->nb_node);
	while (1)
		if (str[*i] == '#')
		{
			if (!(exec_command(obj, str, i)))
				return (0);
		}
		else if (is_node_cond(str, i)) 
		{
			if (!(node = create_node(str, i, obj->nb_node)) ||
				!add_in_lst(obj->lst_node_lk + node->id, node, obj->nb_node))
				return (0);
		}
		else
			break ;
	return (obj->end_node && obj->start_node);
}
