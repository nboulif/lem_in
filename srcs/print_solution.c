/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:20:08 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		copy_in_ouput(t_string *cur_ants, t_string *str,
	t_node_link *node_lk, int nd)
{
	ft_strcpy(str->chaine + str->index, cur_ants->chaine);
	str->index += cur_ants->index;
	str->chaine[str->index++] = '-';
	ft_strcpy(str->chaine + str->index, node_lk->node->name);
	str->index += nd;
	str->chaine[str->index++] = ' ';
}

int			put_in_ouput(t_objectif *obj, t_string *cur_ants, t_string *output,
	t_t_int index)
{
	int				i;
	t_string		*str;
	unsigned long	nd;
	t_node_link		*node_lk;

	if (!init_put_in_ouput(cur_ants, index))
		return (0);
	node_lk = obj->best_sol.way[index.x].nodes_lk;
	i = 0;
	while (1)
	{
		while ((node_lk->node != obj->end_node &&
				node_lk->node->name == node_lk->next->node->name))
			node_lk = node_lk->next;
		str = output + i++ + index.i;
		if (str->index + cur_ants->index + 2 + (nd =
			ft_strlen(node_lk->node->name)) >= (unsigned long)str->size - 1)
			if (!ft_realloc((void **)&str->chaine, &str->size,
					str->size + nd + cur_ants->index + 2 + 1, sizeof(char)))
				return (0);
		copy_in_ouput(cur_ants, str, node_lk, nd);
		if (node_lk->node == obj->end_node)
			return (1);
		node_lk = node_lk->next;
	}
}

int			print_ants_part_three(t_objectif *obj, t_print_ant_utils *u)
{
	u->x = u->i - 1;
	while (++u->x < obj->best_sol.nb_turn + 1)
	{
		if (u->output[u->x].index)
		{
			write(1, u->output[u->x].chaine, u->output[u->x].index - 1);
			write(1, "\n", 1);
		}
		free(u->output[u->x].chaine);
	}
	free(u->cur_ants.chaine);
	free(u->output);
	return (1);
}

int			print_ants_part_two(t_objectif *obj, t_print_ant_utils *u)
{
	u->i = 0;
	u->nb_ants = -1;
	while (u->i_ants < obj->nb_ants)
	{
		u->x = -1;
		if (u->nb_ants == u->i_ants)
			break ;
		u->nb_ants = u->i_ants;
		while (++u->x < obj->best_sol.nb_way && u->i_ants < obj->nb_ants)
		{
			if (obj->best_sol.way[u->x].nb_ants-- <= 0)
				continue ;
			if (!(put_in_ouput(obj, &u->cur_ants,
				u->output, (t_t_int){u->i, u->x, u->i_ants++})))
				return (0);
		}
		write(1, u->output[u->i].chaine, u->output[u->i].index - 1);
		write(1, "\n", 1);
		free(u->output[u->i].chaine);
		u->i++;
	}
	return (print_ants_part_three(obj, u));
}

int			print_ants(t_objectif *obj)
{
	t_print_ant_utils u;

	create_node_tab(obj);
	u.i_ants = 0;
	u.x = -1;
	if (!create_output(&obj->best_sol, &u.output))
		return (0);
	u.cur_ants.size = 10;
	if (!(u.cur_ants.chaine = malloc(sizeof(char) * u.cur_ants.size)))
		exit(write(2, "ERROR\n", 6));
	u.cur_ants.chaine[0] = 'L';
	while (++u.x < obj->best_sol.nb_way)
		obj->best_sol.way[u.x].nb_ants = (obj->best_sol.nb_turn -
			obj->best_sol.way[u.x].len) + 1;
	return (print_ants_part_two(obj, &u));
}
