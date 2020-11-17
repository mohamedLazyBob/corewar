/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 03:33:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/02/22 12:12:37 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isstr_digit(char *str)
{
	while (*str)
	{
		if (ft_isdigit((int)*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
