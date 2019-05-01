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
	t_node_link *n_ln;
	t_edge *e;

	i = way->len - 1;
	way->nodes_lk[i].node = obj->end_node;
	way->nodes_lk[i].next = NULL;
	
	while (i + 1)
	{
		n_ln = &way->nodes_lk[i];
		printf("name %s \n", n_ln->node->name);
		e = n_ln->node->father_edge[obj->sol->nb_way];
		
		
		way->edges_lk[i].edge = e;
		way->edges_lk[i].edge->deja_vu += 1;
		if (way->nodes_lk[i].node == obj->end_node)
			way->edges_lk[i].next = NULL;
		else
			way->edges_lk[i].next = &way->edges_lk[i + 1];

		way->nodes_lk[i - 1].node = n_ln->node->father_node[obj->sol->nb_way];
		way->nodes_lk[i - 1].next = n_ln;

		if(way->nodes_lk[i - 1].node->id != obj->start_node->id)
			way->nodes_lk[i - 1].node->deja_vu += 1;
		
		if (e->node1->id == n_ln->node->id)
		{
			u = e->node1;
			v = e->node2;
			dir = UNIDIR1;
			w = &e->w1;
		}
		else
		{
			u = e->node2;
			v = e->node1;
			dir = UNIDIR2;
			w = &e->w2;
		}

		if (e->direction == BIDIR)
		{
			e->direction = dir;
			*w = -(*w);
		}
		else if (e->direction != NODIR)
		{
			e->direction = NODIR;
			*w = 0;
		}
		--i;

	}


	i = -1;
	while (++i < way->len)
	{
		printf("%d %s   %s -- %s   / w  %d -- %d  / d  %d \n", 
			way->nodes_lk[i].node->deja_vu, way->nodes_lk[i].node->name, 
			way->edges_lk[i].edge->node1->name, way->edges_lk[i].edge->node2->name, 
			way->edges_lk[i].edge->w1, way->edges_lk[i].edge->w2,			
			way->edges_lk[i].edge->direction			
			);
	}

	int z;
	t_edge_link *tmp;

	t_edge_link *e_ln_1;
	t_edge_link *e_ln_2;

	i = -1;
	while (++i < way->len)
	{
		// printf("nameDEBUG 0\n");
		e_ln_2 = &way->edges_lk[i];
		n_ln = &way->nodes_lk[i];
		// printf("nameDEBUG 1\n");

		if (e_ln_2->next && e_ln_2->next->edge->direction == NODIR)
		{
			printf("nameDEBUG 2\n");

			z = obj->sol->nb_way;

			while(z-- > 0)
			{
				e_ln_1 = &obj->sol->way[z].edges_lk[0];
				// e_ln_1 = obj->sol->way[z].edges_lk;

				while(e_ln_1->next && (e_ln_1->next->edge != e_ln_2->next->edge))
					e_ln_1 = e_ln_1->next;
				
				if(e_ln_1->next && (e_ln_1->next->edge == e_ln_2->next->edge))
				{
					printf("nameDEBUG 3\n");

					tmp = e_ln_2->next->next;
					e_ln_2->next = e_ln_1->next->next;
					e_ln_1->next = tmp;
					break;
				}
			}
		}
		// printf("nameDEBUG 3\n");
	}
	
	printf("nameDEBUG 4\n");

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