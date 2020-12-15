/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:44 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/10 18:22:08 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	i = ft_strlen(s1);
	if (!(s2 = ft_strnew(i)))
		return (NULL);
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	return (s2);
}
