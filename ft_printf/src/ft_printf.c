/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:51:50 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:24:27 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	g_fd;

int		va_argnth(va_list ap, char *fmt)
{
	int		i;
	int		nbr;

	i = 0;
	while ((fmt[i] && ft_isdigit(fmt[i])))
		i++;
	if (i != 0 && fmt[i] == '$')
	{
		nbr = ft_atoi(fmt);
		while (nbr && --nbr)
			va_arg(ap, void *);
		return (++i);
	}
	return (0);
}

char	*flag_scope(int *nbr, char *fmt, va_list ap)
{
	int		flags;
	int		pw[2];
	int		pos;

	flags = 0;
	fmt += va_argnth(ap, fmt);
	ft_bzero(pw, sizeof(pw));
	while (*fmt && is_conv_spec(*fmt, FLAGS_BUF) == -1 && !(pos = 0))
	{
		pos += save_width(fmt, &pw[1], ap);
		(void)((fmt[pos] == '.') && (1 == set_flag_on(&flags, POINT)));
		pos += save_precision(fmt + pos, &pw[0], ap, flags);
		(void)(fmt[pos] == '.' && (set_flag_on(&flags, POINT)));
		pos += save_flag(&flags, fmt + pos);
		if (!pos)
			break ;
		fmt += pos;
	}
	if ((!pos && *fmt == '%') && (1 + (*nbr += ft_put_char('%', flags, pw[1]))))
		return (++fmt);
	if (((pos = find_flag(FLAGS_BUF, fmt, 1)) != -1) && fmt++)
		*nbr += g_router[pos](ap, flags, pw[0], pw[1]);
	if ((*fmt == '%' && (fmt + 1)[0] != '%') || *fmt == '{')
		return (flag_scope(nbr, fmt + 1, ap));
	return (fmt);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	int		nbr;
	char	*fmt;

	nbr = 0;
	g_fd = 1;
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

int (*g_router[12])(va_list, int, int, int) =
{
	ft_putc, \
	ft_puts, \
	ft_putptr, \
	ft_putdnbr, \
	ft_putdnbr, \
	ft_putonbr, \
	ft_putunbr, \
	ft_putxnbr, \
	ft_putbxnbr, \
	ft_putfnbr, \
	ft_putenbr, \
	ft_putgnbr, \
};
