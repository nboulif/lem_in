/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_create_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:05:01 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 17:42:38 by nboulif          ###   ########.fr       */
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
