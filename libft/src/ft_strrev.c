/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:45:01 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/14 19:27:27 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*strcopy;
	char	*endstr;
	char	temp;

	endstr = str + ft_strlen(str);
	strcopy = str - 1;
	while (++strcopy < --endstr)
	{
		temp = *endstr;
		*endstr = *strcopy;
		*strcopy = temp;
	}
	return (str);
}
