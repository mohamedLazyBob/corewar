/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:24:56 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/08 15:14:31 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*head;
	t_list	*nxt;

	head = *alst;
	while (head != NULL)
	{
		nxt = head->next;
		(*del)(head->content, head->content_size);
		free(head);
		head = nxt;
	}
	(*alst) = NULL;
}
