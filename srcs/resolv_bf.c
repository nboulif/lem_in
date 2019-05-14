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

int 		check_atomic(t_solution *sol, t_way *way)
{
	t_edge_link		*e_check;
	int 			z;
	
	t_edge_link 	*e_ln;
	t_node			*node;
	int 			check;
	
	check = 1;
	printf("len => %d\n", way->len);

	e_ln = &way->edges_lk[0];
	node = obj->start_node;
	while (e_ln)
	{
		node = get_right_node_in_edge(e_ln->edge, node, 0);

		if (e_ln->next && !node)
		{
			printf("DISCONTINUE\n");
			return (0);
		}
		if (node)
		{
			z = -1;
			while(++z < sol->nb_way)
			{
				e_check = sol->way[z].edges_lk;
				t_node *node_checker = obj->start_node;
				while (e_check)
				{
					node_checker = get_right_node_in_edge(e_check->edge, node_checker, 0);
					if (node_checker == node && node != obj->end_node && node)
					{	

						printf("CROISEMENT  way  %d & %d   |%s|-|%s|  |%s|-|%s|\n",
							sol->nb_way, z, 
							e_ln->edge->node1->name, e_ln->edge->node2->name, e_check->edge->node1->name, e_check->edge->node2->name
						);
						printf("node dv		|%d|-|%d| & |%d|-|%d|\n", e_ln->edge->node1->deja_vu, e_ln->edge->node2->deja_vu, e_check->edge->node1->deja_vu, e_check->edge->node2->deja_vu);
						printf("weight		|%d|-|%d| & |%d|-|%d|\n", e_ln->edge->w1, e_check->edge->w2, e_ln->edge->w1, e_check->edge->w2);
						printf("dir				 |%d| & |%d|\n", e_ln->edge->direction, e_check->edge->direction);
						printf("edge dv			 |%d| & |%d|\n", e_ln->edge->deja_vu, e_check->edge->deja_vu);
						check = 0;
					}
					e_check = e_check->next;
				}
			}
		
		}
		e_ln = e_ln->next;
	}
	
	return (check);
}

int 		find_way(t_solution *sol)
{ 
	t_way 		*way;

	way = &sol->way[sol->nb_way];

	if (!(init_way(way)))
	    return (-1);

	int i;
	i = 0;
	while (i < obj->nb_node)
		obj->lst_node[i++]->deja_vu_in_way = 0;

	if (!apply_algo_bellman_ford(sol))
		return(0);

	printf("cost => %d\n", way->cost);
	
	make_way(sol);
	print_way_status_before_merge(way);
	merge_way(sol);
	int check;
	check = check_atomic(sol, way);
	if (!check)
	{
		printf("\n\nCROSSSSSSSSSSSSSSSSSSING\n\n");	
		return (check);
	}
	print_way_status_after_merge(way);
	return (check);
	
}

void	reset_graph(int nb_way)
{
	int		i;
	t_node	*node;

	i = 0;
	while (i < obj->nb_node)
	{
		node = obj->lst_node[i++];
		node->fathers[nb_way] = (t_father){NULL, NULL, NULL, NULL, 0};
	}
}

void check_bfs(t_solution *sol, t_edge *e, int mode, t_queue *queue)
{
	t_node *u;
	t_node *v;

	if (mode == 1)
	{
		u = e->node1;
		v = e->node2;
	}
	else
	{
		u = e->node2;
		v = e->node1;
	}
	//printf("checking --> (%d)|%s|-(%d)|%s|\n", u->deja_vu, u->name,v->deja_vu, v->name);
	if (u != v && u != obj->end_node
		&& v != obj->start_node &&
		(u->fathers[sol->nb_way].node || u->fathers[sol->nb_way].node_out)
		&& (!u->deja_vu || v->deja_vu ||
		(u->fathers[sol->nb_way].node_out))
		)
	{

		queue->node[queue->size_queue++] = v;
		if (queue->size_queue > obj->nb_node)
			queue->size_queue = 0;

		if (u->deja_vu && v->deja_vu)
		{
			if (v->fathers[sol->nb_way].node_out)
				v->fathers[sol->nb_way].node_out = u;
				v->fathers[sol->nb_way].edge_out = e;
				if (!v->fathers[sol->nb_way].node)
				{
					v->fathers[sol->nb_way].node = u;
					v->fathers[sol->nb_way].edge = e;
					v->fathers[sol->nb_way].mode = 0;
					queue->node[queue->size_queue++] = v;
					if (queue->size_queue > obj->nb_node)
						queue->size_queue = 0;
					t_node *node2;
					for (int i = 0; i < v->nb_edge_f; i++)
					{
						int tmp = v->edge[i]->deja_vu;
						v->edge[i]->deja_vu = 0;
						node2 = get_right_node_in_edge(v->edge[i], v, 1);
						v->edge[i]->deja_vu = tmp;
						if (node2 && node2->deja_vu)
						{
							if (queue->node[queue->index] == v->edge[i]->node1 &&
								v->edge[i]->direction & UNIDIR1)
								check_bfs(sol, v->edge[i], 1, queue);
							else if (queue->node[queue->index] == v->edge[i]->node2 &&
								v->edge[i]->direction & UNIDIR2)
								check_bfs(sol, v->edge[i], 2, queue);
						}
					}
				}
		}
		else
		{
			if (u->deja_vu && !v->deja_vu)
			{
				if (v->fathers[sol->nb_way].node)
					return ;
				v->fathers[sol->nb_way].mode = 1;
			}
			else
			{
				if (v->fathers[sol->nb_way].node)
					return ;
				v->fathers[sol->nb_way].mode = 0;
			}
			v->fathers[sol->nb_way].node = u;
			v->fathers[sol->nb_way].edge = e;
		}
	}
}

int bfs(t_solution *sol)
{
	// int 		i;
	int 		j;
	t_queue		queue;
	t_edge 		*e;

	reset_graph(sol->nb_way);
	//init_dist_deja_vu_lst(obj);
	queue = (t_queue){.index = 0, .node = NULL, .size_queue = 1};
	queue.node = malloc(sizeof(t_node*) * (obj->nb_node + 1));
	//i = -1;
	int o;
	o = -1;

	// o = obj->nb_node;
	// while (--o >= 0)
	queue.node[queue.size_queue] = obj->start_node;
	while (queue.index == queue.size_queue)
	{
		j = -1;
		while (++j < queue.node[queue.index]->nb_edge_f)
		{
			e = queue.node[queue.index]->edge[j];
			if (queue.node[queue.index] == e->node1 && e->direction & UNIDIR1)
				check_bfs(sol, e, 1, &queue);
			else if (queue.node[queue.index] == e->node2 && e->direction & UNIDIR2)
				check_bfs(sol, e, 2, &queue);
		}
		queue.index++;
	}
	//suurballe_formule(obj, sol->nb_way);
	sol->way[sol->nb_way].cost = obj->dists[obj->nb_node - 1];
	free(queue.node);
	if (!obj->end_node->fathers[sol->nb_way].node) //|| dist[obj->nb_node - 1] < 0)
		return(0);
	return(1);
}