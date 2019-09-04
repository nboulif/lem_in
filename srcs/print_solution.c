/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:03:31 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void create_output(t_solution *sol, t_string **output)
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

static int ft_lenstr(long n)
{
	static int nb = 1;
	static int cmp = 1;

	while (cmp * 10 <= n)
	{
		cmp *= 10;
		nb++;
	}
	return (nb);
}

char *ft_itoa_no_m(char *str, int n)
{
	static int size = 0;
	static int last = 1;
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

void put_in_ouput_travel_of_ants(t_objectif *obj, t_solution *sol, t_string *cur_ants, t_string *output, t_t_int index)
{
	int i;
	t_string *str;
	unsigned long nd;
	t_node_link *node_lk;

	nd = 0;
	i = 0;
	if ((cur_ants->index = ft_lenstr(index.i_ants + 1) + 1) >= cur_ants->size - 1)
		if (!ft_realloc((void **)&cur_ants->chaine, &cur_ants->size, cur_ants->size * 2, sizeof(char)))
			exit(1);
	ft_itoa_no_m(cur_ants->chaine + 1, index.i_ants + 1);
	node_lk = sol->way[index.x].nodes_lk;
	while (1)
	{
		while ((node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name))
			node_lk = node_lk->next;
		str = output + i + index.i;
		if (str->index + cur_ants->index + 2 +
				(nd = ft_strlen(node_lk->node->name)) >=
			(unsigned long)str->size - 1)
			if (!ft_realloc((void **)&str->chaine, &str->size,
							str->size + nd + cur_ants->index + 2 + 1, sizeof(char)))
				exit(1);
		ft_strcpy(str->chaine + str->index, cur_ants->chaine);
		str->index += cur_ants->index;
		str->chaine[str->index++] = '-';
		ft_strcpy(str->chaine + str->index, node_lk->node->name);
		str->index += nd;
		str->chaine[str->index++] = ' ';
		if (node_lk->node == obj->end_node)
			return;
		i++;
		node_lk = node_lk->next;
	}
}

void print_ants(t_objectif *obj, t_solution *sol)
{
	t_string *output;
	t_string current_ants;
	int i;
	int x;
	int i_ants;

	i_ants = 0;
	x = -1;
	create_output(sol, &output);
	current_ants.size = 10;
	if (!(current_ants.chaine = malloc(sizeof(char) * current_ants.size)))
		exit(1);
	current_ants.chaine[0] = 'L';
	while (++x < sol->nb_way)
		sol->way[x].nb_ants = (sol->nb_turn - sol->way[x].len) + 1;
	i = 0;
	int nb_ants = -1;
	while (i_ants < obj->nb_ants)
	{
		x = -1;
		if (nb_ants == i_ants)
			break;
		nb_ants = i_ants;
		while (++x < sol->nb_way && i_ants < obj->nb_ants)
		{
			if (sol->way[x].nb_ants-- <= 0)
				continue;
			put_in_ouput_travel_of_ants(obj, sol, &current_ants, output, (t_t_int){i, x, i_ants++});
		}
		write(1, output[i].chaine, output[i].index - 1);
		write(1, "\n", 1);
		free(output[i].chaine);
		i++;
	}
	for (int x = i; x < sol->nb_turn + 1; x++)
	{
		if (output[x].index)
		{
			write(1, output[x].chaine, output[x].index - 1);
			write(1, "\n", 1);
		}
		free(output[x].chaine);
	}
	free(current_ants.chaine);
	free(output);
}