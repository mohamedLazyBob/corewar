/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_macros_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:47:04 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:48:24 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	set_flag(int *flags, int pos)
{
	*flags = (1 << pos) | *flags;
}

/*
** the only use of return is to be able to add the func
** to a logic sentence (ex: someting && set_flag_on)
*/

/*
** ****************************************************************************
*/

int		set_flag_on(int *flags, int pos)
{
	*flags = (1 << pos) | *flags;
	return (1);
}

/*
** ****************************************************************************
*/

void	set_flag_off(int *flags, int pos)
{
	*flags = (~(1 << pos)) & *flags;
}

/*
** ****************************************************************************
*/

void	reset_flags(int *flags)
{
	flags = 0;
}

/*
** ****************************************************************************
*/

int		is_sign(int c)
{
	return (c == '-' || c == '+' || c == ' ');
}
