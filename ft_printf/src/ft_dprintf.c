/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:37:01 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:42:52 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_fd;

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list	ap;
	int		nbr;
	char	*fmt;

	nbr = 0;
	g_fd = fd;
	va_start(ap, format);
	fmt = (char*)format;
	while (*fmt)
	{
		fmt += set_color(fmt);
		if ((*fmt == '%' && *(++fmt)) && *fmt != '%')
		{
			fmt = flag_scope(&nbr, fmt, ap);
			if (*fmt && *fmt != '%')
				nbr += write(g_fd, fmt++, 1);
		}
		else if (*fmt)
			nbr += write(g_fd, fmt++, 1);
	}
	va_end(ap);
	return (nbr);
}
