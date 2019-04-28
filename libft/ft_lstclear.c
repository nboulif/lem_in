/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:52:04 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 15:59:44 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list *begin)
{
	if (begin)
	{
		ft_lstclear(begin->next);
		if (begin->content)
			free(begin->content);
		free(begin);
	}
}
