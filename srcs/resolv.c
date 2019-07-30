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

	i = sol->nb_turn + 1;
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

static int		ft_lenstr(long n)
{
	static int nb = 1;
	static int cmp = 1;

	// printf("n -> %ld", n);
	while ((cmp * 10) <= n)
	{
		cmp *= 10;
		nb++;
	}
	// printf("len -> %d\n", nb);
	return (nb);
}

char			*ft_itoa_no_m(char *str, int n)
{
	static int	size = 0;
	static int  last = 1;
	int ind;

	if (n == last + 1 &&
		ft_lenstr(n) == size)
	{
		ind = size - 1;
		if (str[size - 1] == '9')
		{
			while (str[ind] == '9')
			{
				str[ind] = '0';
				ind--;
			}
			str[ind - 1] += 1;
		}
		else
			str[size - 1] += 1;
        last = n;
		return (str);
	}
	last = n;
	size = ft_lenstr(n);
	str[size] = '\0';
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	put_in_ouput_travel_of_ants(t_objectif *obj, t_solution *sol, t_string *cur_ants, t_string *output, t_t_int index)
{
	int				i;
	t_string		*str;
	t_node_link		*node_lk;

	i = 0;
	if ((cur_ants->index = ft_lenstr(index.i_ants + 1) + 1) >= cur_ants->size - 1)
		if (!ft_realloc((void**)&cur_ants->chaine,
			&cur_ants->size, cur_ants->size * 2, sizeof(char)))
			exit(1);
	ft_itoa_no_m(cur_ants->chaine + 1, index.i_ants + 1);
	node_lk = sol->way[index.x].nodes_lk;
	while (1)
	{
		while (node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name)
			node_lk = node_lk->next;
		str = output + i + index.i;
		if (str->index + cur_ants->index + 2 + node_lk->node->size_name >= str->size - 1)
			if (!ft_realloc((void**)&str->chaine, &str->size,
				str->size * 4, sizeof(char)))
				exit(1);
		ft_strcpy(str->chaine + str->index, cur_ants->chaine);
		str->index += cur_ants->index;
		str->chaine[str->index++] = '-';
		ft_strcpy(str->chaine + str->index, node_lk->node->name);
		str->index += node_lk->node->size_name;
		str->chaine[str->index++] = ' ';
		if (node_lk->node == obj->end_node)
			return ;
		i++;
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
	current_ants.chaine[1] = 0;
	printf("***||nb_turn %d sol->nb_way %d||***\n", sol->nb_turn, sol->nb_way);
	while (++x < sol->nb_way)
		sol->way[x].nb_ants = (sol->nb_turn - sol->way[x].len) + 1;
	i = 0;
	int nb_ants = -1;
	while (i_ants < obj->nb_ants)
	{
		x = -1;
		nb_ants = i_ants;
		while (++x < sol->nb_way && i_ants < obj->nb_ants)
		{
			if (sol->way[x].nb_ants-- <= 0)
				continue ;
			put_in_ouput_travel_of_ants(obj, sol, &current_ants, output, (t_t_int){i, x, i_ants++});
		}
		if (nb_ants == i_ants)
		{
			printf("break prblm\n");
			break;
		}
		i++;
	}
	x = -1;
	while (output[++x].index)
	{
		printf("%.*s\n", output[x].index - 1, output[x].chaine);
		free(output[x].chaine);
	}
	free(output);
}

void		create_node_tab(t_objectif *obj, t_solution *sol)
{
	t_node		*current;
	int			i;
	int			x;
	t_edge_link		*e_ln;

	x = -1;
	while (++x < sol->nb_way)
	{
		i = 0;
		current = obj->start_node;
		sol->way[x].nodes_lk[0].node = current;
		e_ln = sol->way[x].edges_lk;
		while (1)
		{
			current = get_right_node_in_edge(e_ln->edge, current, 0);

			if (!current)
				break;
			sol->way[x].nodes_lk[i + 1].node = current;
			sol->way[x].nodes_lk[i].next = &sol->way[x].nodes_lk[i + 1];
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

// int			fill_min_way(t_objectif *obj, t_solution *sol, int i, int nb_max)
// {
// 	int x = -1;
// 	int objectif_turn_per_way;
// 	int	nb_ants;

// 	// printf("max -> |%d| nb_max -> |%d|\n", sol->way[i].len, nb_max);
// 	objectif_turn_per_way = sol->way[i].len;
// 	nb_ants = obj->nb_ants;
// 	while (++x < sol->nb_way)
// 	{
// 		if (sol->way[x].len == sol->way[i].len)
// 			continue ;
// 		sol->way[x].nb_ants = objectif_turn_per_way - sol->way[x].len + 1;
// 		printf("sol->way[%d].nb_ants |%d| \n", x, sol->way[x].nb_ants);
// 		nb_ants -= sol->way[x].nb_ants;
// 		if ((nb_ants == 0 && x < sol->nb_way - 1) || nb_ants < 0)
// 		{
// 			while (x >= 0)
// 				sol->way[x--].nb_ants = 0;
// 			return (0);
// 		}
// 	}
// 	nb_ants -= (nb_max < nb_ants) ? nb_max : nb_ants;
// 	printf("sol->way[0].nb_ants %d | sol->way[0].len %d | nb_ants / sol->nb_way %f\n", sol->way[0].nb_ants, sol->way[0].len, (float)nb_ants / (float)sol->nb_way);
// 	sol->nb_turn = sol->way[0].nb_ants - !!sol->way[0].nb_ants +
// 				sol->way[0].len +
// 				nb_ants / sol->nb_way +
// 				!!(nb_ants % sol->nb_way);
// 	// printf("sol->nb_turn |%d|\n", sol->nb_turn);
// 	return (1);
// }

// void		evaluate_turn_solution(t_objectif *obj, t_solution *sol)
// {
// 	// int sum;
// 	// int retry;
// 	int nb_ants = 0;
// 	int i;
// 	int max;
// 	int max_ind;
// 	int	nb_max;

// 	i = -1;
// 	if (sol->nb_way == 1)
// 	{
// 		sol->nb_turn = sol->way[0].len + obj->nb_ants - 1;
// 		// printf("sol->nb_turn |%d|\n", sol->nb_turn);
// 		return ;
// 	}
// 	while (1)
// 	{
// 		nb_ants = obj->nb_ants;
// 		max_ind = 0;
// 		max = 0;
// 		while (++i < sol->nb_way)
// 		{
// 			if (max < sol->way[i].len)
// 			{
// 				nb_max = 1;
// 				max = sol->way[i].len;
// 				max_ind = i;
// 			}
// 			else if (max == sol->way[i].len)
// 				nb_max++;
// 		}
// 		if (nb_max == sol->nb_way)
// 		{
// 			sol->nb_turn =	sol->way[0].len +
// 							(obj->nb_ants / sol->nb_way) +
// 							!!(obj->nb_ants % sol->nb_way) - 1;
// 			return ;
// 		}
// 		if (fill_min_way(obj, sol, max_ind, nb_max))
// 			break;
// 		while (--i >= 0)
// 			if (max == sol->way[i].len)
// 				sol->way[i] = sol->way[--sol->nb_way];
// 		sol->nb_turn = INT_MAX;
// 		break;
// 	}
// }

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
		if (best_sol.nb_way && best_sol.nb_turn < next_sol.nb_turn)
		{
			printf("MORE TURN\n");
			//break ;
			continue ;
		}
		for (int i = best_sol.nb_way; i < next_sol.nb_way; i++)
			init_way(obj, &best_sol.way[i]);
	//****** faire une fonction **********
for (int x = 0; x < next_sol.nb_way; x++)
{
	t_edge_link *edges_lk = next_sol.way[x].edges_lk;
	int         y = 0;

	while (edges_lk)
	{
		best_sol.way[x].edges_lk[y].edge = edges_lk->edge;
		best_sol.way[x].edges_lk[y].next = NULL;
		if ((edges_lk = edges_lk->next))
			best_sol.way[x].edges_lk[y].next = &best_sol.way[x].edges_lk[y + 1];
		y++;
	}
	best_sol.way[x].len = next_sol.way[x].len;
}
best_sol.nb_turn = next_sol.nb_turn;
best_sol.nb_way = next_sol.nb_way;
best_sol.len = next_sol.len;
	//****** ****************** **********
		if (best_sol.nb_way == obj->nb_ants)
			break ;
	}
	if (best_sol.nb_way)
	{
		create_node_tab(obj, &best_sol);
		print_ants(obj, &best_sol);
		return (1);
	}
	return (0);
}
