/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:12:50 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstpop(t_list **alst)
{
	t_list	*tmp;
	t_list	*prv;

	if (alst == NULL || *alst == NULL)
		return (NULL);
	tmp = *alst;
	if (tmp->next == NULL)
	{
		*alst = NULL;
		return (tmp);
	}
	prv = tmp;
	while (tmp->next)
	{
		prv = tmp;
		tmp = tmp->next;
	}
	prv->next = NULL;
	return (tmp);
}
