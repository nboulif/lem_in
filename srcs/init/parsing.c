/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:12:31 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 18:40:55 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_node(char *str, int *i)
{
	if (str[*i] == ' ')
		return (0);
	*i -= 1;
	while (str[++(*i)] && str[*i] != '\n')
	{
		if (str[*i] == ' ')
		{
			if (!str[*i + 1] || !check_coord(&str[*i + 1]))
				exit(write(2, "ERROR\n", 13));
			else
			{
				zap_line(str, i);
				return (1);
			}
		}
	}
	return (0);
}

int		is_node_cond(char *str, int *i)
{
	int		nb_space;
	int		x;

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

int		count_node(char *str, t_objectif *info)
{
	int			i;
	int			nb_node;
	long		tmp;

	i = 0;
	nb_node = 0;
	tmp = ft_atol(str);
	if (tmp > INT_MAX || tmp < INT_MIN || !tmp)
		exit(write(2, "ERROR\n", 6));
	info->nb_ants = tmp;
	while (str[i] != '\n')
		if (!str[i] || !ft_isdigit(str[i++]))
			return (0);
	if (!i || !str[++i])
		return (0);
	zap_comm(str, &i);
	while (str[i] && is_node(str, &i))
	{
		nb_node++;
		if (!str[i])
			break ;
		if (str[i] == '#')
			zap_comm(str, &i);
	}
	return (nb_node);
}

int		create_lst_node_tab(t_objectif *obj)
{
	int			j;
	int			k;
	t_node_link	*link;

	if (!(obj->lst_node = (t_node**)malloc(sizeof(t_node) * obj->nb_node)))
		return (0);
	obj->lst_node[0] = obj->start_node;
	obj->lst_node[obj->nb_node - 1] = obj->end_node;
	j = -1;
	k = 1;
	while (++j < obj->nb_node)
	{
		link = obj->lst_node_lk[j];
		while (link)
		{
			if (link->node != obj->start_node && link->node != obj->end_node)
			{
				link->node->id = k;
				obj->lst_node[k++] = link->node;
			}
			link = link->next;
		}
	}
	return (1);
}

int		extract_info(t_objectif *obj, char *str)
{
	int			i;
	clock_t		time;

	time = clock();
	i = 0;
	while (str[i] == '#')
		if (!ft_strncmp(str + i, "##start\n", 8) ||
			!ft_strncmp(str + i, "##end\n", 6))
			return (0);
		else
			zap_line(str, &i);
	if ((obj->nb_node = count_node(str + i, obj)) <= 0)
		return (0);
	zap_line(str, &i);
	while (str[i] == '#' &&
		ft_strncmp(str + i, "##start\n", 8) &&
		ft_strncmp(str + i, "##end\n", 6))
		zap_line(str, &i);
	if (!(make_tab_node(obj, str, &i)) || !create_lst_node_tab(obj))
		return (0);
	if (!make_tab_edge(obj, str, &i))
		return (0);
	fprintf(stderr, "parse time -> %f\n",
		(float)(clock() - time) / C_P_S);
	return (i);
}
