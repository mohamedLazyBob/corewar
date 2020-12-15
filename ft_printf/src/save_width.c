/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:47:35 by fokrober          #+#    #+#             */
/*   Updated: 2019/12/31 22:18:13 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		save_width(char *fmt, int *width, va_list ap)
{
	int		i;
	va_list	ap2;

	i = 0;
	va_copy(ap2, ap);
	while (fmt[0] != '0' && fmt[i] && ft_isdigit(fmt[i]))
		i++;
	if (i != 0)
	{
		*width = ft_atoi(fmt);
		return (i);
	}
	if (fmt[0] == '*')
	{
		i = va_argnth(ap2, fmt + 1);
		(void)((i && ft_atoi(fmt + 1)) && (*width = va_arg(ap2, int)));
		(void)((!i) && (*width = va_arg(ap, int)));
		i++;
	}
	va_end(ap2);
	return (i);
}
