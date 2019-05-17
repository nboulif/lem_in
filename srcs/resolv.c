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

int		create_output(t_solution *sol, t_string **output)
{
	int i;

	i = sol->nb_turn * 4;
	if (!(*output = malloc(sizeof(t_string) * i)))
		return (0);
	while (--i >= 0)
	{
		output[0][i].size = 50;
		if (!(output[0][i].chaine = malloc(sizeof(char) * output[0][i].size)))
			return (0);
		output[0][i].chaine[output[0][i].size - 1] = 0;
		output[0][i].index = 0;
	}
	return (1);
}

int		put_in_ouput_travel_of_ants(t_solution *sol, t_string *cur_ants, t_string *output, t_t_int index)
{
	char			*tmp;
	int				i;
	t_string		*str;
	unsigned long	nd;
	t_node_link		*node_lk;
	t_edge_link		*edge_lk;

	nd = 0;
	i = 0;
	if (!(tmp = ft_itoa(index.i_ants + 1)))
		return (0);
	if ((cur_ants->index = ft_strlen(tmp) + 1) >= cur_ants->size - 1)
		if (!ft_realloc((void**)&cur_ants->chaine, &cur_ants->size, cur_ants->size * 2, sizeof(char)))
			return (0);
	ft_strcpy(cur_ants->chaine + 1, tmp);
	free(tmp);
	node_lk = sol->way[index.x].nodes_lk;
	edge_lk = sol->way[index.x].edges_lk;
	while (1)
	{
		while ((node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name))
		{
			edge_lk = edge_lk->next;
			node_lk = node_lk->next;
		}
		str = output + i + index.i;
		if (str->index + cur_ants->index + 2 +
			(nd = ft_strlen(node_lk->node->name)) >= (unsigned long)str->size - 1)
			if (!ft_realloc((void**)&str->chaine, &str->size,
				str->size + nd + cur_ants->index + 2 + 1, sizeof(char)))
				return (0);
		ft_strcpy(str->chaine + str->index, cur_ants->chaine);
		str->index += cur_ants->index;
		str->chaine[str->index++] = '-';
		ft_strcpy(str->chaine + str->index, node_lk->node->name);
		str->index += nd;
		str->chaine[str->index++] = ' ';
		if (node_lk->node == obj->end_node)
			//sol->way[index.x].node[i++ + nd].name == obj->end_node->name)
			return (1);
		i++;
		edge_lk = edge_lk->next;
		node_lk = node_lk->next;
	}
	return (0);
}

int		print_ants(t_solution *sol)
{
	t_string	*output;
	t_string	current_ants;
	int			i;
	int			x;
	int			i_ants;

	i_ants = 0;
	x = -1;
	if (!create_output(sol, &output))
		return (0);
	current_ants.size = 10;
	if (!(current_ants.chaine = malloc(sizeof(char) * current_ants.size)))
		return (0);
	current_ants.chaine[0] = 'L';
	while (++x <= sol->nb_way && obj->nb_ants >= 0)
	{
		i = -1;
		sol->way[x].nb_ants = sol->nb_turn - sol->way[x].len + 1;
		while (++i < sol->way[x].nb_ants && obj->nb_ants > 0)
		{
			if (!put_in_ouput_travel_of_ants(sol, &current_ants, output, (t_t_int){i, x, i_ants++}))
				return (0);
			obj->nb_ants--;
		}
	}
	x = -1;
	//if (obj->nb_ants)
	//	exit(printf("rest %d ant in obj->nb_ants \n", obj->nb_ants));

	while (++x < sol->nb_turn)
	{
		printf("%.*s\n", output[x].index - 1, output[x].chaine);
		//write(1, output[x].chaine, output[x].index - 1);
		free(output[x].chaine);
		//write(1, "\n", 1);
	}
	return (1);
}

void		evaluate_turn_solution(t_solution *sol)
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
				    nb_ants / i + (nb_ants % i ? 1 : 0);
}

int			resolv()
{
	int res;
	int best_turn;
	int i;
	
	t_solution best_sol;
	t_solution next_sol;

	best_sol = (t_solution){NULL, 0, 0, 0};
	best_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way);
	best_sol.nb_way = 0;

	next_sol = (t_solution){NULL, 0, 0, 0};
	next_sol.way = (t_way*)malloc(sizeof(t_way) * obj->max_way);
	next_sol.nb_way = 0;
	
	obj->dists = (int *)malloc(sizeof(int) * ((obj->nb_node * 2) + 1) );
	
	i = 0;
	while (i++ < obj->max_way)
	{
		printf(" \n\nSTART ITERATION => %d\n\n", best_sol.nb_way);

		res = find_way(&next_sol);
		
		if (!(res))
		{
			// printf("NO MORE WAY\n");
			break;
		}
		else if (res == -1)
		{
			printf("ERROR RESOLV\n");
			return (-1);
		}

		
		++next_sol.nb_way;
		evaluate_turn_solution(&next_sol);

		printf("turn best vs current  |%d|-|%d| v2\n", best_turn, next_sol.nb_turn);
		printf("\nEND ITERATION => %d \n", best_sol.nb_way);
		if (best_sol.nb_way && best_turn < next_sol.nb_turn)
		{
			// printf("MORE TURN\n");
			break ;
		}

		best_sol = next_sol;
		best_turn = best_sol.nb_turn;

		if (best_sol.nb_way == obj->nb_ants)
			break ;
	}

	if (best_sol.nb_way)
	{
		print_way(&best_sol);
		if (!print_ants(&best_sol))
			return (0);
		
		printf("nb_turn %d\n", best_turn);
		return (1);
	}
	return (0);
	
}
