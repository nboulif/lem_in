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

void	create_output(t_solution *sol, t_string **output)
{
	int i;

	i = sol->nb_turn * 4;
	if (!(*output = malloc(sizeof(t_string) * i)))
		exit(1);
	while (--i >= 0)
	{
		output[0][i].size = 50;
		if (!(output[0][i].chaine = malloc(sizeof(char) * output[0][i].size)))
			exit(1);
		output[0][i].chaine[output[0][i].size - 1] = 0;
		output[0][i].index = 0;
	}
}

void	put_in_ouput_travel_of_ants(t_objectif *obj, t_solution *sol, t_string *cur_ants, t_string *output, t_t_int index)
{
	char			*tmp;
	int				i;
	t_string		*str;
	unsigned long	nd;
	t_node_link		*node_lk;
	// t_edge_link		*edge_lk;

	nd = 0;
	i = 0;
	if (!(tmp = ft_itoa(index.i_ants + 1)))
		exit(1);
	if ((cur_ants->index = ft_strlen(tmp) + 1) >= cur_ants->size - 1)
		if (!ft_realloc((void**)&cur_ants->chaine, &cur_ants->size, cur_ants->size * 2, sizeof(char)))
			exit(1);
	ft_strcpy(cur_ants->chaine + 1, tmp);
	free(tmp);
	node_lk = sol->way[index.x].nodes_lk;
	// edge_lk = sol->way[index.x].edges_lk;
	while (1)
	{
		while ((node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name))
		{
			// edge_lk = edge_lk->next;
			node_lk = node_lk->next;
		}
		str = output + i + index.i;
		if (str->index + cur_ants->index + 2 +
			(nd = ft_strlen(node_lk->node->name)) >= (unsigned long)str->size - 1)
			if (!ft_realloc((void**)&str->chaine, &str->size,
				str->size + nd + cur_ants->index + 2 + 1, sizeof(char)))
				exit(1);
		ft_strcpy(str->chaine + str->index, cur_ants->chaine);
		str->index += cur_ants->index;
		str->chaine[str->index++] = '-';
		ft_strcpy(str->chaine + str->index, node_lk->node->name);
		str->index += nd;
		str->chaine[str->index++] = ' ';
		if (node_lk->node == obj->end_node)
			//sol->way[index.x].node[i++ + nd].name == obj->end_node->name)
			return ;
		i++;
		// edge_lk = edge_lk->next;
		node_lk = node_lk->next;
	}
}

void	print_ants(t_objectif *obj, t_solution *sol)
{
	t_string	*output;
	t_string	current_ants;
	int			i;
	int			x;
	int			i_ants;

	i_ants = 0;
	x = -1;
	create_output(sol, &output);
	current_ants.size = 10;
	if (!(current_ants.chaine = malloc(sizeof(char) * current_ants.size)))
		exit(1);
	current_ants.chaine[0] = 'L';
	while (++x <= sol->nb_way && obj->nb_ants >= 0)
	{
		i = -1;
		sol->way[x].nb_ants = sol->nb_turn - sol->way[x].len + 1;
		while (++i < sol->way[x].nb_ants && obj->nb_ants > 0)
		{
			put_in_ouput_travel_of_ants(obj, sol, &current_ants, output, (t_t_int){i, x, i_ants++});
			obj->nb_ants--;
		}
	}
	x = -1;
	//if (obj->nb_ants)
	//	exit(printf("rest %d ant in obj->nb_ants \n", obj->nb_ants));

	while (++x < sol->nb_turn)
	{
		printf("%.*s\n", output[x].index - 1, output[x].chaine);
		// write(1, output[x].chaine, output[x].index - 1);
		free(output[x].chaine);
		//write(1, "\n", 1);
	}
}

void		create_node_tab(t_objectif *obj, t_solution *sol)
{
	t_node		*current;
	// t_edge_link *edge;
	int			i;
	int			x;
	t_edge_link		*e_ln;

	x = -1;
	while (++x < sol->nb_way)
	{
		// printf("way n %d :\n------------------\n", x);
		i = 0;
		current = obj->start_node;
		sol->way[x].nodes_lk[0].node = current;
		e_ln = sol->way[x].edges_lk;
		// printf("cur |%s| |%s|-|%s|\n", current->name,
		// e_ln->edge->node1->name,
		// e_ln->edge->node2->name);
		while (1)
		{
			current = get_right_node_in_edge(e_ln->edge, current, 0);
			// if (e_ln->edge->node2 == current)
			// 	current = e_ln->edge->node1;
			// else
			// 	current = e_ln->edge->node2;
			if (!current)
				break;
			sol->way[x].nodes_lk[i + 1].node = current;
			sol->way[x].nodes_lk[i].next = &sol->way[x].nodes_lk[i + 1];
			// printf("cur |%s| |%s|-|%s|\n", current->name,
			// e_ln->edge->node1->name,
			// e_ln->edge->node2->name);
			e_ln = e_ln->next;
			if (current->name == obj->end_node->name)
			{
				sol->way[x].nodes_lk[i + 1].next = NULL;
				break;
			}
			i++;
		}
		sol->way[x].nodes_lk = sol->way[x].nodes_lk->next;
		// printf("------------------\n");
	}
}

void		evaluate_turn_solution(t_objectif *obj, t_solution *sol)
{
	int i;
	int sum;
	int nb_ants;

	sum = 0;
	i = 0;
	while (i < sol->nb_way)
		sum += sol->way[i++].len;
	nb_ants = obj->nb_ants - i;
	while (sum % i)
	{
		sum++;
		if (--nb_ants == 0)
			break ;
	}
	sol->nb_turn =  sum / i +
				    nb_ants / i +
					!!(nb_ants % i);
}

int			resolv(t_objectif *obj)
{
	int res;
	int best_turn;
	int i;
	
	t_solution best_sol;
	t_solution next_sol;

	best_sol = (t_solution){NULL, 0, 0, 0};
	obj->max_way++;
	best_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way);
	best_sol.nb_way = 0;

	next_sol = (t_solution){NULL, 0, 0, 0};
	next_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way);
	next_sol.nb_way = 0;
	
	obj->dists = (int *)malloc(sizeof(int) * ((obj->nb_node * 2) + 1) );
	
	i = 0;
	while (i++ < obj->max_way)
	{
		// printf(" \n\nSTART ITERATION => %d\n\n", best_sol.nb_way);

		res = find_way(obj, &next_sol);
		
		if (!(res))
		{
			printf("NO MORE WAY\n");
			break;
		}
		else if (res == -1)
		{
			printf("ERROR RESOLV\n");
			return (-1);
		}

		++next_sol.nb_way;
		evaluate_turn_solution(obj, &next_sol);

		// printf("turn best vs current  |%d|-|%d| v2\n", best_turn, next_sol.nb_turn);
		// sleep(1);
		// printf("\nEND ITERATION => %d \n", best_sol.nb_way);
		if (best_sol.nb_way && best_turn < next_sol.nb_turn)
		{
			// printf("MORE TURN\n");
			break ;
		}
		best_sol = next_sol;
		best_turn = best_sol.nb_turn;
		// printf("ici %d\n", best_sol.nb_way);
		if (best_sol.nb_way == obj->nb_ants)
			break ;
	}

	if (best_sol.nb_way)
	{
		// print_way(obj, &best_sol);
		create_node_tab(obj, &best_sol);
		// print_way(obj, &best_sol);
		print_ants(obj, &best_sol);
		// printf("nb_turn %d\n", best_turn);
		return (1);
	}
	return (0);
	
}
