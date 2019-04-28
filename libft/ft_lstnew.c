/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:13:11 by rhunders          #+#    #+#             */
/*   Updated: 2018/10/08 01:59:11 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*new_element;
	size_t	i;

	i = -1;
	if ((new_element = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content_size &&
		(new_element->content = malloc(sizeof(char) * content_size)) == NULL)
		return (NULL);
	else if (content == NULL)
	{
		new_element->content = NULL;
		new_element->content_size = 0;
	}
	else
	{
		new_element->content_size = content_size;
		while (++i < content_size)
			*(char*)(new_element->content + i) = *(char*)(content + i);
	}
	new_element->next = NULL;
	return (new_element);
}
/*
**#include <stdio.h>
**
**int main()
**{
**	t_list *y;
**	size_t	x = 1;
**
**	y = ft_lstnew (NULL, 36);
**	if (y != 0 && (y->content_size != 0 || y->content != NULL))
**		printf("error1\n");
**	free(y);
**	y = ft_lstnew(&x, sizeof(size_t));
**	if (y != NULL)
**	{
**		if (&x == y->content)
**			printf("error2\n");
**		if (*(size_t*)y->content != 1)
**			printf("error3\n");
**		if (y->content_size != sizeof(size_t))
**			printf("error4\n");
**		if (y->next != 0)
**			printf("error5\n");
**	}
**	printf ("%d\nsize = %zu\n", *(int*)(y->content), y->content_size);
**	return (0);
**}
*/
