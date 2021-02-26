/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:15:12 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/29 20:05:56 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	if (content == NULL)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
		return (new_node);
	}
	new_node->content = malloc(content_size);
	if (new_node->content == NULL)
	{
		ft_memdel((void **)&new_node);
		return (NULL);
	}
	ft_memcpy(new_node->content, content, content_size);
	new_node->content_size = content_size;
	return (new_node);
}
