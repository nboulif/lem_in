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


void check_negative_cycle(t_objectif *obj, int **dist)
{
	int i;
	int u;
	int v;

	i = -1;
	while (++i < obj->nb_edge)
    {
		u = obj->lst_edge[i].node1->id;
		v = obj->lst_edge[i].node2->id;
        if ((*dist)[u] != __INT_MAX__ && (*dist)[u] + obj->lst_edge[i].w1 < (*dist)[v]) 
            printf("Graph contains negative weight cycle\n"); 
    } 
	
}
int init_dist_lst(t_objectif *obj, int **dist)
{
	(*dist) = (int *)malloc(sizeof(int) * obj->nb_node);
	for (int i = 0; i < obj->nb_node; i++)
	{
		if (obj->lst_node[i]->id == obj->start_node->id)
			(*dist)[obj->lst_node[i]->id] = 0;
		else
			(*dist)[obj->lst_node[i]->id] = __INT_MAX__;	
	}
	return (1);
}


int make_way(t_objectif *obj, t_way *way)
{
	int i;
	int dir;
	int *w;
	t_node *u;
	t_node *v;

	i = way->len - 1;
	way->node[i] = obj->end_node;


	while (i + 1)
	{
		// printf("name %s \n", way->node[i]->name);

		way->edge[i] = way->node[i]->father_edge[obj->sol->nb_way];

		if (way->edge[i]->node1->id == way->node[i]->id)
		{
			u = way->edge[i]->node1;
			v = way->edge[i]->node2;
			dir = UNIDIR1;
			w = &way->edge[i]->w1;
		}
		else
		{
			u = way->edge[i]->node2;
			v = way->edge[i]->node1;
			dir = UNIDIR2;
			w = &way->edge[i]->w2;
		}

		if (way->edge[i]->direction == BIDIR)
		{
			way->edge[i]->direction = dir;
			*w = -(*w);					
		}
		else
		{
			way->edge[i]->direction = NODIR;
			*w = 0;		
		}

		// printf("name %s -- %s, weight %d -- %d, dir %d\n", way->edge[i]->node1->name, way->edge[i]->node2->name, way->edge[i]->w1, way->edge[i]->w2,  way->edge[i]->direction);
		
		way->node[i - 1] = way->node[i]->father_node[obj->sol->nb_way];
		way->node[i - 1]->deja_vu += 1;

		if (way->node[i - 1]->deja_vu > 1)
		{
			
		}

		--i;
	}

	i = -1;
	while (++i < way->len)
	{
		printf("%d %s   %s -- %s   / w  %d -- %d  / d  %d \n", way->node[i]->deja_vu, way->node[i]->name, 
			way->edge[i]->node1->name, way->edge[i]->node2->name, 
			way->edge[i]->w1, way->edge[i]->w2,			
			way->edge[i]->direction			
			);
	}
	return(1);
}

void check_bellman_ford(t_objectif *obj, int **dist, t_edge *e, int mode)
{
	t_node *u;
	t_node *v;
	int 	w;
	int 	dir;
	
	if (mode == 1)
	{
		u = e->node1;
		v = e->node2;
		w = e->w1;
		dir = UNIDIR1;
	}
	else
	{
		u = e->node2;
		v = e->node1;
		w = e->w2;
		dir = UNIDIR2;
	}
	
	if (
		(e->direction == BIDIR || e->direction == dir) &&
		u->id != obj->end_node->id &&
		(
			!u->deja_vu || !u->father_node[obj->sol->nb_way] ||
			( 
				u->father_node[obj->sol->nb_way] 
				&&
				( 
					(!v->deja_vu && u->father_node[obj->sol->nb_way]->deja_vu) 
					|| 
					(v->deja_vu && !u->father_node[obj->sol->nb_way]->deja_vu) 
				)
			)
		) &&
		(*dist)[u->id] != __INT_MAX__ && (*dist)[u->id] + w < (*dist)[v->id]
		) 
	{
		printf("2 ");

		(*dist)[v->id] = (*dist)[u->id] + w;
		// if (
		// 	(
		// 		(!u->deja_vu) || 
		// 		( 
		// 			(u->father_node[obj->sol->nb_way]) 
		// 			&&
		// 			( 
		// 				(!v->deja_vu && u->father_node[obj->sol->nb_way]->deja_vu) 
		// 				|| 
		// 				(v->deja_vu && !u->father_node[obj->sol->nb_way]->deja_vu) 
		// 			)
		// 		)
		// 	)
		// )
		// {
			v->father_node[obj->sol->nb_way] = u;
			v->father_edge[obj->sol->nb_way] = e;
		// }
	}
}

void apply_algo_bellman_ford(t_objectif *obj, int **dist)
{
	int i;
	int j;

	t_edge *e;

	i = 0;
	while (++i < obj->nb_node)
	{
		j = -1;
		while (++j < obj->nb_edge_f)
		{
			e = obj->lst_edge_ord[j];
			check_bellman_ford(obj, dist, e, 1);
			check_bellman_ford(obj, dist, e, 2);
			
		}
	}
	printf("- \n");
	check_negative_cycle(obj, dist);
}


int find_way(t_objectif *obj)
{ 
    int			*dist; 
	t_way 		*way;

	way = &obj->sol->way[obj->sol->nb_way];

	if (!(init_dist_lst(obj, &dist)) || !(init_way(obj, way)))
	    return (-1);

	apply_algo_bellman_ford(obj, &dist);
	// apply_algo_bfs(obj, &dist);
	if (dist[obj->nb_node - 1] == __INT_MAX__)
		return(0);

	way->cost = dist[obj->nb_node - 1];
	
	t_node *curr;

	way->len = -1;
	curr = obj->end_node;
	while (curr)
	{
		way->len++;
		// printf("name => %s\n", curr->name);
		curr = curr->father_node[obj->sol->nb_way];
	}
	printf("cost => %d\n", way->cost);
	printf("len => %d\n", way->len);

	make_way(obj, way);

    return (1);
} 