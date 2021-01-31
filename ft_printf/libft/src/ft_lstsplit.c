/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:36:11 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/14 19:21:10 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_zina(char *s, int *i, char c, t_list **temp)
{
	int		size;
	char	buff[65535];

	size = ft_charinword(s, *i, c);
	ft_memcpynull(buff, s + *i, size);
	(*temp)->next = ft_lstnew(buff, size + 1);
	(*temp) = (*temp)->next;
	(*i) += size;
}

t_list		*ft_lstsplit(char *s, char c)
{
	int		i;
	int		size;
	char	buff[65535];
	t_list	*head;
	t_list	*temp;

	if (!s || !c)
		return (NULL);
	i = 0;
	head = (t_list*)malloc(sizeof(t_list));
	while (s[i] == c && s[i])
		i++;
	size = ft_charinword(s, i, c);
	ft_memcpynull(buff, s + i, size);
	head = ft_lstnew(buff, size + 1);
	temp = head;
	i += head->content_size;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else if (s[i] != c && s[i])
			ft_zina(s, &i, c, &temp);
	}
	return (head);
}
