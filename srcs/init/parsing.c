/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:12:31 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/12 17:12:33 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_node(char *str, int *i)
{
	int 		nb_space;

	if (str[*i] == ' ')
		return (0);
	nb_space = 0;
	*i -= 1;
	while (str[++(*i)] && str[*i] != '\n')
	{
		if (str[*i] == ' ')
		{
			if (nb_space == 2)
			{
				zap_line(str, i);
				return (--(*i) & 0);
			}
			nb_space++;
			continue ;
		}
		if (nb_space && !ft_isdigit(str[*i]))
		{
			zap_line(str, i);
			return (--(*i) & 0);
		}
	}
	return (nb_space == 2 && str[*i - 1] != ' ');
}

int		is_node_cond(char *str, int *i)
{
	int 		nb_space;
	int 		x;

	if (str[*i] == ' ')
		return (0);
	nb_space = 0;
	x = *i - 1;
	while (str[++x] && str[x] != '\n')
	{
		if (str[x] == ' ')
		{
			if (nb_space == 2)
				return (0);
			nb_space++;
			continue ;
		}
		if (nb_space && !ft_isdigit(str[x]))
			return (0);
	}
	return (nb_space == 2 && str[x - 1] != ' ');
}

int		count_node(char *str)
{
	int			i;
	int			nb_node;

	i = 0;
	nb_node = 0;
	obj->nb_ants = ft_atoi(str);
	while (str[i] != '\n')
		if (!str[i] || !ft_isdigit(str[i++]))
			return (0);
	if (i++ == 0)
		return (0);
	zap_comm(str, &i);
	while (str[i] && is_node(str, &i))
	{
		nb_node++;
		if (!str[i])
			break ;
		i++;
		if (str[i] == '#')
			zap_comm(str, &i);
	}
	return (nb_node);
}

int extract_info(char *str)
{
	int			i;
	int			var;

	obj->nb_node = count_node(str);
	i = 0;
	zap_line(str, &i);
	if ((var = make_tab_node(str, &i)) == -1)
		exit(printf("MALLOC ERROR\n"));

	int j;
	int k;
	t_node_link *link;

	obj->lst_node = (t_node**)malloc(sizeof(t_node) * obj->nb_node);
	j = -1;
	k = 1;
	obj->lst_node[0] = obj->start_node;
	obj->start_node->id = 0;
	obj->lst_node[obj->nb_node - 1] = obj->end_node;
	obj->end_node->id = obj->nb_node - 1;
	while (++j < obj->nb_node)
	{
		link = obj->lst_node_lk[j];
		while (link)
		{
			if (link->node != obj->start_node &&
			link->node != obj->end_node)
			{
				link->node->id = k;
				obj->lst_node[k++] = link->node;
			}
			link = link->next;
		}
	}

	if (var && !make_tab_edge(str, &i))
	{
		exit(printf("ERROR\n"));
	}
	return (1);
}
