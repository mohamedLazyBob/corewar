/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:21:10 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/13 22:03:47 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*head;

	if (!(head = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		head->content = NULL;
		head->content_size = 0;
		head->next = NULL;
		return (head);
	}
	else if (!(head->content = malloc((content_size + 1) * sizeof(*content))))
	{
		free(head);
		return (NULL);
	}
	ft_memcpy(head->content, content, content_size);
	head->content_size = content_size;
	head->next = NULL;
	return (head);
}
