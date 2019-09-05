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

long		ft_atol(const char *str)
{
	long		i;
	long	resultat;
	int		signe;

	signe = 1;
	i = 0;
	resultat = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' ||
			str[i] == '\f')
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1] > 47 && str[i + 1] < 58)
		signe = (str[i] == '+') ? 1 : -1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + str[i] - '0';
		if (resultat < 0)
			return ((signe < 0) ? 0 : -1);
		i++;
	}
	return (signe * resultat);
}

int			number_check(char *str)
{
	long	number;

	number = ft_atol(str);
	return (number <= INT_MAX && number >= INT_MIN);
}

int			check_coord(char *str)
{
	int i;

	if (!ft_isdigit(str[0]))
	{
		if (str[0] != '-' && str[0] != '+')
			return (0);
		i = 1;
	}
	else
		i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (!(str[i] != ' ' || !ft_isdigit(str[i + 1]) ||
		!number_check(str) || !number_check(&str[i + 1])));
}

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
				exit(write(2, "BAD NUMBER FOR COORD\n", 22));
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

int		count_node(char *str, t_objectif *info)
{
	int			i;
	int			nb_node;
	long		tmp;

	i = 0;
	nb_node = 0;
	tmp = ft_atol(str);
	if (tmp > INT_MAX || tmp < INT_MIN || !tmp)
		exit(write(2, "BAD NB OF ANTS\n", 16));
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

int extract_info(t_objectif *obj, char *str)
{
	int			i;
	int			j;
	int			k;
	t_node_link	*link;

	clock_t time = clock();
	i = 0;
	while (str[i] == '#')
		if (!ft_strncmp(str + i, "##start\n", 8) ||
			!ft_strncmp(str + i, "##end\n", 6))
			exit(write(2, "\"##start\" ot \"##end\" before ants\n", 34));
		else
			zap_line(str, &i);
	if ((obj->nb_node = count_node(str + i, obj)) <= 0)
		return (0);
	zap_line(str, &i);
	while (str[i] == '#' &&
		ft_strncmp(str + i, "##start\n", 8) &&
		ft_strncmp(str + i, "##end\n", 6))
		zap_line(str, &i);
	if (!(make_tab_node(obj, str, &i)))
		exit(write(2, "MALLOC ERROR\n", 14));
	if (!(obj->lst_node = (t_node**)malloc(sizeof(t_node) * obj->nb_node)))
		return (0);
	obj->lst_node[0] = obj->start_node;
	obj->start_node->id = 0;
	obj->lst_node[obj->nb_node - 1] = obj->end_node;
	obj->end_node->id = obj->nb_node - 1;
	j = -1;
	k = 1;
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
	if (!make_tab_edge(obj, str, &i))
		exit(printf("ERROR IN EDGE\n"));
	fprintf(stderr, "parse time -> %f\n", (float)(clock() - time) / CLOCKS_PER_SEC);
	return (!str[i]);
}
