/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:05:01 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:42:51 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	nm.chaine[nm.index] = 0;
	if (!(node = malloc_node(nb_node, 1)) || (nm.index != nm.size &&
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
	static int			index = 0;
	int					i;

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
	go == 6 ? obj->end_node = node : 0;
	go == 8 ? obj->start_node = node : 0;
	return (1);
}

int			make_tab_node(t_objectif *obj, char *str, int *i)
{
	t_node	*node;

	if (!(obj->lst_node_lk = malloc(sizeof(t_node_link*) * obj->nb_node)))
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
	obj->start_node ? obj->start_node->id = 0 : 0;
	obj->end_node ? obj->end_node->id = obj->nb_node - 1 : 0;
	return (obj->end_node && obj->start_node);
}
