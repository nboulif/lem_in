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
** si une node n'a qu'un tube ou moins alors on peut le supprimer directement.
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
			if (link->node->nb_tube_f > obj->max_link)
				obj->max_link = link->node->nb_tube_f;
			link = link->next;
 		}
 	}
	obj->max_way = ft_min(obj->start_node->nb_tube_f, obj->end_node->nb_tube_f,
						obj->max_link);
	obj->max_way = (obj->max_way < obj->nb_ants) ? obj->max_way : obj->nb_ants;
}

#include <time.h>

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
	write(1, str, size - 1);
	if (str[size - 2] != '\n')
		ft_putchar('\n');
	free(str);
	ft_putchar('\n');
	
	if ((res = resolv(&obj)) == -1)
	{
		printf("Error Resolv\n");
		return (0);
	}
	
	return (0);
}
