/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 16:41:55 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/05 18:22:59 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int c)
{
	return ((c <= 'z' && c >= 'a') ||
			(c >= 'A' && c <= 'Z'));
}
/*
**#include <stdio.h>
**
**int main()
**{
**	char str[] = "bonjour morsure cheval livre";
**
**	printf("%d", ft_isalpha('0'));
**	printf("%d", ft_isalpha('y'));
**	return(0);
**}
*/
