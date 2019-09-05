/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:20:35 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				create_output(t_solution *sol, t_string **output)
{
	int i;

	i = sol->nb_turn + 1;
	if (!(*output = malloc(sizeof(t_string) * i)))
		return (free_output_error(sol, output, i));
	while (--i >= 0)
	{
		output[0][i].size = 50;
		if (!(output[0][i].chaine = malloc(sizeof(char) * output[0][i].size)))
			return (free_output_error(sol, output, i));
		output[0][i].chaine[output[0][i].size - 1] = 0;
		output[0][i].index = 0;
	}
	return (1);
}

static int		ft_lenstr(long n)
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

char			*ft_itoa_no_m_part_two(char *str, int n, int last, int size)
{
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

char			*ft_itoa_no_m(char *str, int n)
{
	static int	size = 0;
	static int	last = 1;
	int			ind;

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
	return (ft_itoa_no_m_part_two(str, n, last, size));
}

int				init_put_in_ouput(t_string *cur_ants, t_t_int index)
{
	if ((cur_ants->index =
		ft_lenstr(index.i_ants + 1) + 1) >= cur_ants->size - 1)
		if (!ft_realloc((void **)&cur_ants->chaine,
			&cur_ants->size, cur_ants->size * 2, sizeof(char)))
			return (0);
	ft_itoa_no_m(cur_ants->chaine + 1, index.i_ants + 1);
	return (1);
}
