/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:38:53 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 15:35:32 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_lst;
	t_list	*current;
	int		i;

	i = 0;
	if (lst == NULL)
		return (NULL);
	begin_lst = (*f)(lst);
	lst = lst->next;
	while (lst != NULL)
		if (i == 1)
		{
			current->next = (*f)(lst);
			current = current->next;
			lst = lst->next;
		}
		else
		{
			current = (*f)(lst);
			begin_lst->next = current;
			lst = lst->next;
			i = 1;
		}
	return (begin_lst);
}
