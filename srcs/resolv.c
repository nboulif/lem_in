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
	while (1)
	{
		while (node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name)
			node_lk = node_lk->next;
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
	while (++x <= sol->nb_way)
		sol->way[x].nb_ants = sol->nb_turn - sol->way[x].len + 1;
	i = 0;
	int nb_ants = 0;
	while (i_ants < obj->nb_ants)
	{
		x = -1;
		nb_ants = i_ants;
		while (++x < sol->nb_way && i_ants < obj->nb_ants)
		{
			if (sol->way[x].nb_ants-- <= 0)
				sol->way[x] = sol->way[--sol->nb_way];
			put_in_ouput_travel_of_ants(obj, sol, &current_ants, output, (t_t_int){i, x, i_ants++});
		}
		if (nb_ants == i_ants)
			break;
		i++;
	}
	x = -1;
	while (++x < sol->nb_turn)
	{
		write(1, output[x].chaine, output[x].index - 1);
		free(output[x].chaine);
		write(1, "\n", 1);
	}
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
	next_sol = (t_solution){NULL, 0, 0, 0};
	obj->max_way++;
	if (!(best_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way)) ||
		!(next_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way)) ||
		!(obj->dists = (int*)malloc(sizeof(int) * ((obj->nb_node * 2) + 1))))
		exit(1);
	i = 0;
	while (i++ < obj->max_way)
	{
		res = find_way(obj, &next_sol);
		if (!res)
			break;
		else if (res == -1)
			return (-1);
		++next_sol.nb_way;
		evaluate_turn_solution(obj, &next_sol);
		if (best_sol.nb_way && best_turn < next_sol.nb_turn)
			break ;
		best_sol = next_sol;
		best_turn = best_sol.nb_turn;
		if (best_sol.nb_way == obj->nb_ants)
			break ;
	}
	if (!best_sol.nb_way)
	{
		init_way(obj, next_sol.way, 0);
		return (0);
	}
	create_node_tab(obj, &best_sol);
	print_ants(obj, &best_sol);
	init_way(obj, next_sol.way, 0);
	return (1);
}
