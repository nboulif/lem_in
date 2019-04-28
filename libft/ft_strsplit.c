/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:08:56 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/12 14:58:20 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*ft_malloc2d(char *str, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if ((tab = malloc(sizeof(char) * i + 1)) == NULL)
		return (NULL);
	tab[i] = '\0';
	i = 0;
	while (str[i] && str[i] != c)
	{
		tab[i] = str[i];
		i++;
	}
	return (tab);
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		i2;
	int		nb_word;
	char	**tab;

	if (s == NULL || !c)
		return (NULL);
	i = -1;
	i2 = -1;
	nb_word = ft_count_word(s, c);
	if ((tab = (char**)malloc(sizeof(char*) * (nb_word + 1))) == NULL)
		return (NULL);
	tab[nb_word] = NULL;
	while (s[++i])
		if (s[i] != c && (++i2 > -5))
		{
			if ((tab[i2] = ft_malloc2d((char*)(s + i), c)) == NULL)
			{
				ft_tabclear(&tab);
				return (NULL);
			}
			while (s[i + 1] && s[i + 1] != c)
				i++;
		}
	return (tab);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	char **tab;
**	char *str = NULL;
**	tab = ft_strsplit("bonjour le monde *", 0);
**	if (tab != NULL)
**	{
**		while (*tab != NULL)
**		{
**			printf("%s\n",*tab);
**			tab++;
**		}
**	}
**	return(0);
**}
*/
