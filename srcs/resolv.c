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
	printf("***||nb_turn %d sol->nb_way %d||***\n", sol->nb_turn, sol->nb_way);
	while (++x < sol->nb_way)
		sol->way[x].nb_ants = (sol->nb_turn - sol->way[x].len) + 1;
	i = 0;
	int nb_ants = -1;
	while (i_ants < obj->nb_ants)
	{
		x = -1;
		if (nb_ants == i_ants)
		{
			printf("break prblm\n");
			break;
		}
		nb_ants = i_ants;
		while (++x < sol->nb_way && i_ants < obj->nb_ants)
		{
			if (sol->way[x].nb_ants-- <= 0)
				continue ;
			put_in_ouput_travel_of_ants(obj, sol, &current_ants, output, (t_t_int){i, x, i_ants++});
		}
		i++;
	}
	x = -1;
	//if (obj->nb_ants)
	//	exit(printf("rest %d ant in obj->nb_ants \n", obj->nb_ants));

	while (output[++x].index)
	{
		printf("%.*s\n", output[x].index - 1, output[x].chaine);
		//write(1, output[x].chaine, output[x].index - 1);
		//write(1, "\n", 1);
		free(output[x].chaine);
	}
	free(output);
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

// ***********************************************************
// **************  old estimate max way   ********************
// ***********************************************************

// void		evaluate_turn_solution(t_objectif *obj, t_solution *sol)
// {
// 	int i;
// 	int sum;
// 	int nb_ants;
// 	int retry;

// 	retry = 0;
// 	sum = 0;
// 	i = 0;
// 	while (i < sol->nb_way)
// 		sum += sol->way[i++].len;
// 	nb_ants = obj->nb_ants - i;
// 	if (sum % i)
// 	{
// 		--nb_ants;
// 		while (sum % i)
// 		{
// 			sum++;
// 			if (--nb_ants == 0)
// 				break ;
// 		}
// 	}
// 	sol->nb_turn =  sum / i +
// 				    nb_ants / i +
// 					!!(nb_ants % i);
// 	i = -1;
// 	while (++i < sol->nb_way)
// 		if (sol->way[i].len > sol->nb_turn)
// 		{
// 			sol->way[i--] = sol->way[--sol->nb_way];
// 			retry = 1;
// 		}
// 	if (retry)
// 		evaluate_turn_solution(obj, sol);
// }

// *************************************************************
// *************************************************************
void		evaluate_turn_solution_old(t_objectif *obj, t_solution *sol)
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

int			fill_min_way(t_objectif *obj, t_solution *sol, int i, int nb_max)
{
	int x = -1;
	int objectif_turn_per_way;
	int	nb_ants;

	printf("max -> |%d| nb_max -> |%d|\n", sol->way[i].len, nb_max);
	objectif_turn_per_way = sol->way[i].len;
	nb_ants = obj->nb_ants;
	while (++x < sol->nb_way)
	{
		if (sol->way[x].len == sol->way[i].len)
			continue ;
		sol->way[x].nb_ants = objectif_turn_per_way - sol->way[x].len + 1;
		nb_ants -= sol->way[x].nb_ants;
		if ((nb_ants == 0 && x < sol->nb_way - 1) || nb_ants < 0)
		{
			while (x >= 0)
				sol->way[x--].nb_ants = 0;
			return (0);
		}
	}
	nb_ants -= (nb_max < nb_ants) ? nb_max : nb_ants;
	sol->nb_turn = sol->way[0].nb_ants - 1 +
				sol->way[0].len +
				nb_ants / sol->nb_way +
				!!(nb_ants % sol->nb_way);
	// printf("sol->nb_turn |%d|\n", sol->nb_turn);
	return (1);
}

void		evaluate_turn_solution(t_objectif *obj, t_solution *sol)
{
	// int sum;
	// int retry;
	int nb_ants = 0;
	int i;
	int max;
	int max_ind;
	int	nb_max;

	i = -1;
	if (sol->nb_way == 1)
	{
		sol->nb_turn = sol->way[0].len + obj->nb_ants - 1;
		// printf("sol->nb_turn |%d|\n", sol->nb_turn);
		return ;
	}
	while (1)
	{
		nb_ants = obj->nb_ants;
		max_ind = 0;
		max = 0;
		while (++i < sol->nb_way)
		{
			if (max < sol->way[i].len)
			{
				nb_max = 1;
				max = sol->way[i].len;
				max_ind = i;
			}
			else if (max == sol->way[i].len)
				nb_max++;
		}
		if (fill_min_way(obj, sol, max_ind, nb_max))
			break;
		while (--i >= 0)
			if (max == sol->way[i].len)
				sol->way[i] = sol->way[--sol->nb_way];
		sol->nb_turn = INT_MAX;
		break;
	}
}

int			resolv(t_objectif *obj)
{
	int res;
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
	
	obj->dists = (int *)malloc(sizeof(int) * ((obj->nb_node * 2) + 1));

	i = 0;
	best_sol.nb_turn = INT_MAX;
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
		evaluate_turn_solution_old(obj, &next_sol);
		printf("old -> |%d| &", next_sol.nb_turn);
		evaluate_turn_solution(obj, &next_sol);
		printf("new -> |%d|\n", next_sol.nb_turn);
		// print_way(obj, &next_sol);
		printf("***||evaluate_turn_solution NEXT -> %d||***\n", next_sol.nb_turn);

		// printf("turn best vs current  |%d|-|%d| v2\n", best_turn, next_sol.nb_turn);
		// sleep(1);
		// printf("\nEND ITERATION => %d \n", best_sol.nb_way);
		if (best_sol.nb_way && best_sol.nb_turn < next_sol.nb_turn)
		{
			printf("MORE TURN\n");
			break ;
		}
		else
		{
			init_way(obj, &best_sol.way[next_sol.nb_way - 1]);
			for (int x = 0; x < next_sol.nb_way; x++)
			{
				ft_memcpy(best_sol.way[x].nodes_lk, next_sol.way[x].nodes_lk, sizeof(t_node_link) * next_sol.way[x].len);
				ft_memcpy(best_sol.way[x].edges_lk, next_sol.way[x].edges_lk, sizeof(t_edge_link) * next_sol.way[x].len); 
				best_sol.way[x].len = next_sol.way[x].len;
			}
			best_sol.nb_turn = next_sol.nb_turn;
			best_sol.nb_way = next_sol.nb_way;
			best_sol.len = next_sol.len;
			//ft_memcpy(best_sol.way, next_sol.way, sizeof(t_way));
			//ft_memcpy(&best_sol, &next_sol, sizeof(t_solution));
			//best_sol = next_sol;
			//best_turn = best_sol.nb_turn;
		}
		// printf("ici %d\n", best_sol.nb_way);
		if (best_sol.nb_way == obj->nb_ants)
			break ;
		// clone_way(obj, &next_sol, &best_sol);
	}
	if (best_sol.nb_way)
	{
		create_node_tab(obj, &best_sol);
		printf("***||evaluate_turn_solution BEST -> %d||***\n", best_sol.nb_turn);
		print_ants(obj, &best_sol);
		return (1);
	}
	return (0);
}
