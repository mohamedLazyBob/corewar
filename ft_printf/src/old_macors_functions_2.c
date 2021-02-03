/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_macors_functions_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:47:42 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:49:15 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ****************************************************************************
*/

int		is_conv(int c)
{
	return (c != EXPO && c != STRING && c != XFLOAT);
}

/*
** ****************************************************************************
*/

int		is_on(int flags, int pos)
{
	return (((1 << pos) & flags) != 0);
}