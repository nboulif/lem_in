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
#include <fcntl.h>
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
int fd;
int		read_all(char **str)
{
	int				index;
	int				size;
	int				ret;

	size = SIZE_BUFF + 1;
	if (!(*str = malloc(size * sizeof(char))))
		return (0);
	index = 0;
	while ((ret = read(fd, *str + index, SIZE_BUFF)) > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < SIZE_BUFF)
		{
			// printf("realloc 1\n");
			if (ft_realloc((void**)str, &index, index, sizeof(char)) &&
				!((*str)[index] = 0))
				return (index);
			return (0);
		}
		// printf("realloc 2\n");
		if (index + SIZE_BUFF >= size - 1)
			if (!ft_realloc((void**)str, &size, size * 2, sizeof(char)))
				return (0);
	}
	// printf("realloc 3\n");
	if (index < size && !ft_realloc((void**)str, &index, index, sizeof(char)))
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

t_father* alloc_t_father(t_objectif *obj, int mode)
{
	static t_father	*tab = NULL;
	static size_t	index = 0;

	if (!mode)
	{
		free(tab);
		return (NULL);
	}
	if (tab == NULL)
	{
		if (!(tab = malloc(sizeof(t_father) * (size_t)(obj->max_way + 1) * (size_t)(obj->nb_node + 1))))
			return (NULL);
	}
	index += (obj->max_way + 1);
	return (&tab[index - (obj->max_way + 1)]);
}

t_node** alloc_t_node_star(t_objectif *obj, int mode)
{
	static t_node	**tab = NULL;
	static size_t	index = 0;

	if (!mode)
	{
		free(tab);
		return (NULL);
	}
	if (tab == NULL)
	{
		if (!(tab = malloc(sizeof(t_node*) * (size_t)(obj->max_way + 1) * ((size_t)obj->nb_node + 1))))
			return (NULL);
	}
	index += (obj->max_way + 1);
	return (&tab[index - (obj->max_way + 1)]);
}

t_edge** alloc_t_edge_star(t_objectif *obj, int mode)
{
	static t_edge	**tab;
	static size_t	index = 0;

	if (!mode)
	{
		free(tab);
		return (NULL);
	}
	if (tab == NULL)
	{
		if (!(tab = malloc(sizeof(t_edge*) * (size_t)(obj->max_way + 1) * ((size_t)obj->nb_node + 1))))
			return (NULL);
	}
	index += (obj->max_way + 1);
	return (&tab[index - (obj->max_way + 1)]);
}

int init_max_father_in_node(t_objectif *obj)
{
	int i;
	int	x;
	t_node *node;

	i = -1;
	while (++i < obj->nb_node)
	{
		node = obj->lst_node[i];
		if (node->nb_edge_f == 1 &&
			node != obj->start_node &&
			node != obj->end_node)
		{
			if (node == node->edge[0]->node2)
				delete_this_edge(node->edge[0]->node1,
								node->edge[0], obj);
			else
				delete_this_edge(node->edge[0]->node2,
								node->edge[0], obj);
			continue ;
		}
		if (!(node->fathers = alloc_t_father(obj, 1)) ||
			!(node->father_node = alloc_t_node_star(obj, 1)) ||
			!(node->father_edge = alloc_t_edge_star(obj, 1)))
			return (0);
		x = 0;
		while (x < (obj->max_way + 1))
		{
			node->fathers[x] = (t_father){NULL, NULL, NULL, NULL, 0};
			node->father_node[x] = NULL;
			node->father_edge[x++] = NULL;
		}
	}
	return (1);
}

void print_main_info(t_objectif obj)
{
	printf("nb_node => %d\n", obj.nb_node);
	printf("nb_edge => %d\n", obj.nb_edge);
	printf("nb_edge_f => %d\n", obj.nb_edge_f);
	printf("max_way => %d\n", obj.max_way);
}

int main(int argc, char **argv)
{
	char			*str;
	t_objectif		obj;
	int				size;
	int				res;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			fd = 0;
	}
	else
		fd = 0;
	ft_memset(&obj, 0, sizeof(t_objectif));
	str = NULL;
	if (!(size = read_all(&str)) ||
		!extract_info(&obj, str) || !init_resolv(&obj))
	{
		printf("Error init\n");
		return (0);
	}
	estimate_max_way(&obj);
	print_node_and_edge(str, size);

	if (!obj.max_way)
	{
		printf("NO WAY AVAILABLE\n");
		return (0);
	}
	
	// print_main_info(obj);
	
	if (!(init_max_father_in_node(&obj)))
	{
		printf("Error init_max_father\n");
		return (0);
	}
	if ((res = resolv(&obj)) == -1)
	{
		printf("Error Resolv\n");
		exit(0);
	}
	// *** free ***
alloc_t_father(&obj, 0);
alloc_t_node_star(&obj, 0);
alloc_t_edge_star(&obj, 0);
	// *** *** ***
	return (1);
}
