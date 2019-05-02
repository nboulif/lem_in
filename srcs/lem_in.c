/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:42:54 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/27 02:17:44 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** le nombre de tour que vont prendre les fourmis à arriver à l'objectif est
** equivalent au nombre de nodes dans le plus long chemin trouvé + le nombre de
** fourmi qui vont l'emprunter.
*/

/*
** si toute les salles sont relier à toutes les autres alors tte les salles sont
** les chemins les plus court vers l'objectif donc pas besoin de chercher
** les chemins ils sont évident.
*/

/*
** si une salle est relié au start et à l'objectif alors le chemin
** le plus court c'est start-[le noeud]-end.(donc pas de recherche)
*/

/*
** si une node n'a qu'un edge ou moins alors on peut le supprimer directement.
*/

int		read_all(char **str)
{
	int				index;
	int				size;
	int				ret;

	size = SIZE_BUFF + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return (0);
	index = 0;
	while ((ret = read(0, *str + index, SIZE_BUFF)) > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < SIZE_BUFF)
		{
			if (ft_realloc((void**)str, &index, index + 1, sizeof(char)) &&
				!((*str)[index] = 0))
				return (index);
			return (0);
		}
		if (index + SIZE_BUFF >= size - 1)
			if (!ft_realloc((void**)str, &size, size * 2, sizeof(char)))
				return (0);
	}
	if (index < size && !ft_realloc((void**)str, &index, index + 1, sizeof(char)))
		return (0);
	return (index);
}

void estimate_max_way(t_objectif *obj)
{
	int				i;
	t_node_link 	*link;

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

int init_max_father_in_node(t_objectif *obj)
{
	int i;
	t_node *node;

	i = -1;
	while (++i < obj->nb_node)
	{
		node = obj->lst_node[i];
		if (!(node->father_node = malloc((obj->max_way + 1) * sizeof(t_node*))) ||
			!(node->father_edge = malloc((obj->max_way + 1) * sizeof(t_edge*))))
			return (0);
		ft_memset(node->father_node, 0, (obj->max_way + 1) * sizeof(t_node*));
		ft_memset(node->father_edge, 0, (obj->max_way + 1) * sizeof(t_edge*));
		
	}
	return (1);
}

void print_main_info(t_objectif obj)
{
// print_node_and_edge(str, size);
	printf("nb_node => %d\n", obj.nb_node);
	printf("nb_edge => %d\n", obj.nb_edge);
	printf("nb_edge_f => %d\n", obj.nb_edge_f);
	printf("max_way => %d\n", obj.max_way);
	sleep(1);
}

int main(void)
{
	char			*str;
	t_objectif		obj;
	int				size;
	int res;
	
	ft_memset(&obj, 0, sizeof(t_objectif));
	str = NULL;
	if (!(size = read_all(&str)) ||
		!extract_info(&obj, str) || !init_resolv(&obj))
	{
		printf("Error init\n");
		return (0);
	}
	estimate_max_way(&obj);

	if (!obj.max_way)
	{
		printf("NO WAY AVAILABLE\n");
		return (0);
	}
	
	print_main_info(obj);
	
	if (!(init_max_father_in_node(&obj)))
	{
		printf("Error init_max_father\n");
		return (0);
	}
	if ((res = resolv(&obj)) == -1)
	{
		printf("Error Resolv\n");
		return (0);
	}

	
	return (1);
}
