/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 00:01:04 by mzaboub           #+#    #+#             */
/*   Updated: 2020/02/19 16:15:43 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_numbercmp(const char *s1, const char *s2)
{
	char				*p1;
	char				*p2;
	unsigned long long	l1;
	unsigned long long	l2;

	p1 = (char*)s1;
	p2 = (char*)s2;
	l1 = ft_strlen(p1);
	l2 = ft_strlen(p2);
	if (l1 != l2)
		return (l1 - l2);
	if ((*p1 != *p2) || (*p1 == '\0') || (*p2 == '\0'))
		return (*p1 - *p2);
	else
		return (ft_strcmp(s1 + 1, s2 + 1));
}
