/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:21:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:21:40 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int init_way(t_objectif *obj, t_way *way)
{
	if (!(way->nodes_lk = (t_node_link *)malloc(sizeof(t_node_link) * (obj->nb_node + 1))) ||
		!(way->edges_lk = (t_edge_link *)malloc(sizeof(t_edge_link) * (obj->nb_node + 1))))
	{
		free(way->nodes_lk);
		return (0);
	}
	return (1);
}