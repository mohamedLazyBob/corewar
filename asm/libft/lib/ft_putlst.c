/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:32:25 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putlst(t_list *lst)
{
	if (lst == NULL)
	{
		ft_putstr("empty list");
		return ;
	}
	while (lst)
	{
		ft_putstr("\"");
		if (lst->content != NULL)
			ft_putstr(lst->content);
		else
			ft_putstr("NULL");
		ft_putstr("\"");
		if (lst->next)
			ft_putstr(" -> ");
		lst = lst->next;
	}
}
