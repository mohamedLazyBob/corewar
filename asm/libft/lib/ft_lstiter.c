/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:51:19 by mesafi            #+#    #+#             */
/*   Updated: 2020/03/05 16:18:36 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*node;
	t_list	*temporal;

	node = lst;
	while (node != NULL)
	{
		temporal = node->next;
		(*f)(node);
		node = temporal;
	}
}
