/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc_and_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 02:08:32 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/31 22:15:46 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		ft_putc(va_list ap, int flags, int precision, int width)
{
	unsigned char	c;
	int				ret;

	(void)precision;
	c = (char)va_arg(ap, int);
	(width < 0) ? ((width *= -1) && (set_flag_on(&flags, MINUS))) : 1;
	ret = width;
	if (width > 0 && is_on(flags, MINUS))
	{
		write(1, &c, 1);
		while (--width)
			write(1, " ", 1);
		return (ret);
	}
	else if (width > 0 && !is_on(flags, MINUS))
	{
		while (--width)
			write(1, " ", 1);
		write(1, &c, 1);
		return (ret);
	}
	else
		write(1, &c, 1);
	return (1);
}

int		ft_put_char(char c, int flags, int width)
{
	char	pad;
	int		ret;

	ret = width;
	if (width > 0 && is_on(flags, MINUS))
	{
		write(1, &c, 1);
		while (--width)
			write(1, " ", 1);
		return (ret);
	}
	else if (width > 0 && !is_on(flags, MINUS))
	{
		pad = is_on(flags, ZERO) ? '0' : ' ';
		while (--width)
			write(1, &pad, 1);
		write(1, &c, 1);
		return (ret);
	}
	else
		write(1, &c, 1);
	return (1);
}

int		ft_puts(va_list ap, int flags, int precision, int width)
{
	char	*s;
	int		len;

	s = va_arg(ap, char*);
	if (!s)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(s);
	set_flag_on(&flags, STRING);
	s = build_result(flags, s, precision, width);
	return (ft_putxstr(s));
}
