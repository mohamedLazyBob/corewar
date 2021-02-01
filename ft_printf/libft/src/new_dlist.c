/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:23 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/27 09:02:25 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlist.h>

t_dlist		*new_dlist(void const *content, size_t size)
{
	t_dlist		*node;

	if (!(node = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	if (!(node->content = (void *)malloc(size)))
		return (NULL);
	if (content == NULL)
	{
		node->content = NULL;
		node->size = 0;
	}
	else
	{
		ft_memcpy(node->content, content, size);
		node->size = size;
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
