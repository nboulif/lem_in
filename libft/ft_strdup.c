/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:02:37 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 17:01:42 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*str_clone;
	int		i;
	int		i2;

	i = 0;
	i2 = -1;
	while (src[i])
		i++;
	if ((str_clone = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	while (++i2 <= i)
		str_clone[i2] = src[i2];
	return (str_clone);
}
/*
**#include <stdio.h>
**int main(int argc, char *argv[])
**{
**	if (argc == 2)
**		printf("%s\n", ft_strdup(argv[1]));
**	return (0);
**}
*/
