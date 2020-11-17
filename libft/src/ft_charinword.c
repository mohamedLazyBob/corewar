/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charinword.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:27:54 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/14 19:20:47 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_charinword(char *str, size_t i, char stop)
{
	size_t	begin;

	begin = i;
	while (str[i] != stop && str[i])
		i++;
	return (i - begin);
}
