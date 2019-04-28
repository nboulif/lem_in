/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:46:52 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 02:05:41 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strrimlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	while (i > 1 && (s[i - 1] == ' ' || s[i - 1] == '\t' ||
				s[i - 1] == '\n'))
		i--;
	return (i);
}

char		*ft_strtrim(const char *s)
{
	char	*str;
	int		size;
	int		i;

	i = -1;
	if (s == NULL)
		return (NULL);
	while ((*s == ' ' || *s == '\t' || *s == '\n') && *s)
		s += 1;
	size = (int)ft_strrimlen(s);
	if ((str = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	str[size] = '\0';
	while (++i < size)
		str[i] = (char)s[i];
	return (str);
}
/*
**#include <stdio.h>
**
**int main()
**{
**		printf("result = %s\n",ft_strtrim("  \t\n \t \n  bonjour \t \n \t"));
**	return(0);
**}
*/
