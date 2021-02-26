/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:50:02 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2));
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, s1);
	ft_strcat(p, s2);
	return (p);
}
