/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_mid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 06:39:50 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/11 15:34:25 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_list	*ft_lst_read(int fd)
{
	t_list	*begin_list;
	t_list	*current;
	int		ret;
	char	c[BUFF_SIZE];

	if (!(current = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	begin_list = current;
	while ((ret = read(fd, c, BUFF_SIZE)) > 0)
	{
		if (!(current->content = malloc(sizeof(char) * ret + 1)))
			return (NULL);
		ft_memcpy((char*)current->content, c, ret);
		current->content_size = ret;
		*(char*)(current->content + ret) = '\0';
		if (!(current->next = (t_list*)malloc(sizeof(t_list))))
		{
			if (begin_list)
				ft_lstclear(begin_list);
			return (NULL);
		}
		current = current->next;
	}
	current->next = NULL;
	return (begin_list);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	int fd;
**	t_list *begin_list;
**	t_list *current;
**
**	fd = open("Makefile", O_RDONLY);
**	current = ft_lst_read(fd);
**	begin_list = current;
**	while (current->next != NULL)
**	{
**		ft_putstr((char*)current->content);
**		current = current->next;
**	}
**	return (0);
**}
*/
