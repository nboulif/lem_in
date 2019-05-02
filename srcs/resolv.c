/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:03:31 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int		resolv(t_objectif *obj)
{
	int res;

	obj->sol = (t_solution*)malloc(sizeof(t_solution));
	obj->sol->way = (t_way*)malloc(sizeof(t_way) * obj->max_way);
	obj->sol->nb_way = 0;
	
	printf("max_way => %d \n\n", obj->max_way);

	while (1)
	// while (1)
	{
		printf(" \n\nSTART ITERATION => %d\n\n", obj->sol->nb_way);

		res = find_way(obj);
		printf("\nEND ITERATION => %d \n", obj->sol->nb_way);
		if (!(res) || res == -1)
		{
			return (res);
		}
		++obj->sol->nb_way;

	}

	// obj->sol->nb_way++;
	return (1);
}