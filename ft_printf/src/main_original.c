/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 05:38:31 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:43:37 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

extern	int	g_fd;

int		ft_putptr(va_list ap, int flags, int precision, int width)
{
	set_flag_on(&flags, POINTER);
	set_flag_on(&flags, HASH);
	set_flag_on(&flags, LLONG);
	return (ft_putxnbr(ap, flags, precision, width));
}

int		ft_putgnbr(va_list ap, int flags, int precision, int width)
{
	(void)(precision + flags + width);
	write(g_fd, "", 1);
	va_arg(ap, void *);
	return (0);
}
