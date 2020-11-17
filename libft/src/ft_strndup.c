/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:20:22 by del-alj           #+#    #+#             */
/*   Updated: 2019/10/18 10:49:49 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	if (n == 0)
		return (ft_strnew(0));
	if (!(str = ft_strnew(n)))
		return (NULL);
	ft_strncpy(str, s1, n);
	return (str);
}
