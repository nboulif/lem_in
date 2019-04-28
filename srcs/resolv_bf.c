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

int add_brother_in_queue_bf(t_objectif *obj, t_node *node, t_queue *queue, int iter)
{
	int i;
	t_node *next;
	int W;

	i = -1;
	printf("fsdfds \n");
	while (++i < node->nb_tube_f)
	{
		if (!(next = get_right_node_in_tube(node, i)) || next == obj->start_node)
			continue;
		W = get_right_W_in_tube(node, i);
		if (next->deja_vu != iter)
		{
			queue->node[queue->size_queue++] = next;
			if (queue->size_queue == obj->nb_node)
				queue->size_queue = 0;
			next->deja_vu = iter;
		}
		if (next->D > node->D + W && next != node->father_node[0] && node->D != __INT_MAX__)
		{
			next->father_node[0] = node;
			next->father_tube[0] = node->tube[i];
			next->D = node->D + W;
			obj->changement = 1;
		}
	}
	return (2);
}

t_solution find_way_bf2(t_objectif *obj, t_solution cur)
{
	t_solution sol;
	t_queue queue;
	t_node *current;
	int i;

	//printf("BELLMAN FORD %d\n", bl++);
	sol = (t_solution){NULL, cur.nb_way + 1, 0, 0};
	queue = (t_queue){NULL, 0, 0};

	if (!init_solution(obj, &sol, &queue))
		return ((t_solution){NULL, 0, 0, 0});
	if (cur.way && !(clone_way(obj, &sol, &cur)))
		return ((t_solution){NULL, 0, 0, 0});
	
	obj->changement = 1;
	i = -1;
	init_graph_bf(obj, 1);
	while (1)
	{
		//if (x == (obj->nb_tube * obj->nb_node) / 2)
		//	printf("bl try %d\n", x + 1);
		obj->changement = 0;
		current = obj->start_node;
		while (1)
		{
			add_brother_in_queue_bf(obj, current, &queue, i + 2);
			if (queue.index == queue.size_queue)
				break;
			current = queue.node[queue.index % obj->nb_node];
			queue.node[queue.index++ % obj->nb_node] = NULL;
		}
		if (!obj->end_node->deja_vu || (obj->end_node->D == __INT_MAX__))
			return ((t_solution){NULL, 0, 0, 0});
		if (!obj->changement || ++i > obj->nb_tube)
		{
			if (!obj->end_node->father_tube || !obj->end_node->father_tube[0])
				return ((t_solution){NULL, 0, 0, 0});
			make_way(obj, &sol);
			return (sol);
		}
		init_graph_bf(obj, 0);
	}
	return ((t_solution){NULL, 0, 0, 0});
}

void printArr(t_objectif *obj, int dist[],  int pred[], int V) 
{ 
	printf("Vertex   Dist from Src    NAME  --  PARENT\n"); 
	for (int i = 0; i < V; ++i)
	{
		if (pred[i] >= 0)
		{
			printf("%d \t %d \t\t %s -- %s\n", i, dist[i], obj->lst_node[i]->name, obj->lst_node[pred[i]]->name); 
		}
		else
		{
			printf("%d \t %d \t\t %s -- ??? \n", i, dist[i], obj->lst_node[i]->name); 
		}
		
		
	}
} 

void init_dist_pred_lst(t_objectif *obj, int **dist)
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

t_solution find_way_bf(t_objectif *obj, t_solution cur)
{ 
	(void)cur;

    int			*dist; 
	int			i;
	t_node		**waay;


	dist = (int *)malloc(sizeof(int) * obj->nb_node);
	waay = (t_node **)malloc(sizeof(t_node *) * obj->nb_node);

	init_dist_pred_lst(obj, &dist);
	apply_algo(obj, &dist);
	check_negative_cycle(obj, &dist);

	i = 0;
	waay[i] = obj->end_node;
	while (waay[i]->id != obj->start_node->id)
	{
		printf("%s  --  %s\n", waay[i]->father_tube[0]->node1->name,  
			waay[i]->father_tube[0]->node2->name);
		++i;
		waay[i] = waay[i - 1]->father_node[0];
	}
	
	printf("\nlen => %d \n\n", i);

	while (i--)
		ft_putendl(waay[i]->name);
	
    return ((t_solution){NULL, 0, 0, 0});
} 