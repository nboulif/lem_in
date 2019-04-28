/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 04:18:20 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 16:58:24 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst && alst[0] && new)
	{
		while (alst[0]->next != NULL)
			alst[0] = alst[0]->next;
		alst[0]->next = new;
		new->next = NULL;
	}
}
