/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv_bf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:29:23 by nboulif           #+#    #+#             */
/*   Updated: 2019/04/28 09:29:24 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int get_right_W_in_tube(t_node *node, int i)
{
	if (node == node->tube[i]->node1)
		return (node->tube[i]->w1);
	return (node->tube[i]->w2);
}


void init_dist_lst(t_objectif *obj, int **dist)
{
	for (int i = 0; i < obj->nb_node; i++)
	{
		if (obj->lst_node[i]->id == obj->start_node->id)
			(*dist)[obj->lst_node[i]->id] = 0;
		else
			(*dist)[obj->lst_node[i]->id] = __INT_MAX__;	
	}
}

void apply_algo(t_objectif *obj, int **dist)
{
	int i;
	int j;

	int u;
	int v;

	i = 0;
	while (++i < obj->nb_node)
	{
		j = -1;
		while (++j < obj->nb_tube)
		{
			u = obj->lst_tube[j].node1->id;
			v = obj->lst_tube[j].node2->id;
			if ((*dist)[u] != __INT_MAX__ && (*dist)[u] + obj->lst_tube[j].w1 < (*dist)[v]) 
			{
				(*dist)[v] = (*dist)[u] + obj->lst_tube[j].w1;
				obj->lst_node[v]->father_node[0] = obj->lst_tube[j].node1;
				obj->lst_node[v]->father_tube[0] = &obj->lst_tube[j];
			}

			if ((*dist)[v] != __INT_MAX__ && (*dist)[v] + obj->lst_tube[j].w2 < (*dist)[u]) 
			{
				(*dist)[u] = (*dist)[v] + obj->lst_tube[j].w2;
				obj->lst_node[u]->father_node[0] = obj->lst_tube[j].node2;
				obj->lst_node[u]->father_tube[0] = &obj->lst_tube[j];

			}
		}
	}
}

void check_negative_cycle(t_objectif *obj, int **dist)
{
	int i;
	int u;
	int v;

	i = -1;
	while (++i < obj->nb_tube)
    {
		u = obj->lst_tube[i].node1->id;
		v = obj->lst_tube[i].node2->id;
        if ((*dist)[u] != __INT_MAX__ && (*dist)[u] + obj->lst_tube[i].w1 < (*dist)[v]) 
            printf("Graph contains negative weight cycle"); 
    } 
	
}

void reverse_way(t_objectif *obj, t_way *way)
{
	(void)obj;

	int i;
	t_node		*tmp_node;
	// t_tube		*tmp_tube;
	
	i = -1;
	while (++i < way->len / 2 + way->len % 2)
	{
		tmp_node = way->node[i];
		way->node[i] = way->node[way->len - i];
		way->node[way->len - i] = tmp_node;

		// tmp_tube = way->tube[i];
		// way->tube[i] = way->tube[way->len - i];
		// way->tube[way->len - i] = tmp_tube;
	}
	
	way->node[way->len] = obj->end_node;
	
}

t_way *find_way_bf(t_objectif *obj)
{ 
    int			*dist; 
	int			i;
	t_way		*way;

	dist = (int *)malloc(sizeof(int) * obj->nb_node);
	way = (t_way *)malloc(sizeof(t_way));
	way->node = (t_node **)malloc(sizeof(t_node *) * obj->nb_node);
	way->tube = (t_tube **)malloc(sizeof(t_tube *) * obj->nb_tube);

	init_dist_lst(obj, &dist);
	apply_algo(obj, &dist);
	check_negative_cycle(obj, &dist);

	
	i = 0;
	way->cost = dist[obj->nb_node - 1];
	way->node[i] = obj->end_node;
	while (way->node[i]->id != obj->start_node->id)
	{
		printf("%s  --  %s\n", way->node[i]->father_tube[0]->node1->name,  
			way->node[i]->father_tube[0]->node2->name);
		++i;
		way->node[i] = way->node[i - 1]->father_node[0];
		way->tube[i] = way->node[i - 1]->father_tube[0];
	}
	printf("\nlen => %d \n\n", i);
	way->len = i;

	reverse_way(obj, way);

	i = -1;
	while (++i < way->len + 1)
		printf("%s \n", way->node[i]->name);
	
    return (way);
} 