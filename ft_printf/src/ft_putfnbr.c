/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 05:03:04 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:28:58 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

extern	int	g_fd;

int		ft_putfnbr(va_list ap, int flags, int precision, int width)
{
	t_buffer	node;
	double		nbr;
	t_int32		len;

	if (is_on(flags, BLONG))
		return (ft_putlfnbr(ap, flags, precision, width));
	len = DBL_DIGITS;
	if (precision > len)
		len += precision;
	if (width > len)
		len += width;
	nbr = va_arg(ap, double);
	if (!(node.buff = (char*)malloc(len * sizeof(char))))
		exit(1);
	node.max_len = len - 1;
	node.precision = precision;
	node.width = width;
	node.flags = flags;
	node.bol = 0;
	print_double(nbr, &node, 0);
	len = write(g_fd, node.buff, ft_strlen(node.buff));
	ft_memdel((void**)&node.buff);
	return (len);
}

int		ft_putlfnbr(va_list ap, int flags, int precision, int width)
{
	t_buffer	node;
	long double	nbr;
	t_int32		len;

	len = LDBL_DIGITS;
	if (precision > len)
		len += precision;
	if (width > len)
		len += width;
	nbr = va_arg(ap, long double);
	if (!(node.buff = (char*)malloc(len * sizeof(char))))
		exit(1);
	node.max_len = len - 1;
	node.precision = precision;
	node.width = width;
	node.flags = flags;
	node.bol = 0;
	print_long_double(nbr, &node, 0);
	len = ft_strlen(node.buff);
	write(g_fd, node.buff, len);
	ft_memdel((void**)&node.buff);
	return (len);
}

int		ft_putenbr(va_list ap, int flags, int precision, int width)
{
	t_buffer	*node;
	double		nbr;
	t_int32		len;

	if (is_on(flags, BLONG))
		return (ft_putlenbr(ap, flags, precision, width));
	(!(node = (t_buffer*)malloc(sizeof(t_buffer)))) ? (exit(1)) : 1;
	len = LDBL_DIGITS;
	if (precision > len)
		len += precision;
	if (width > len)
		len += width;
	nbr = va_arg(ap, double);
	(!(node->buff = (char*)malloc(len * sizeof(char)))) ? (exit(1)) : 1;
	node->max_len = len - 1;
	node->precision = precision;
	node->width = width;
	node->flags = flags;
	node->bol = 1;
	print_double(nbr, node, 1);
	len = ft_strlen(node->buff);
	write(g_fd, node->buff, len);
	ft_memdel((void**)&node->buff);
	ft_memdel((void**)&node);
	return (len);
}

int		ft_putlenbr(va_list ap, int flags, int precision, int width)
{
	t_buffer	node;
	long double	nbr;
	t_int32		len;

	len = LDBL_DIGITS;
	if (precision > len)
		len += precision;
	if (width > len)
		len += width;
	nbr = va_arg(ap, long double);
	if (!(node.buff = (char*)malloc(len * sizeof(char))))
		exit(1);
	node.max_len = len - 1;
	node.precision = precision;
	node.width = width;
	node.flags = flags;
	node.bol = 1;
	print_long_double(nbr, &node, 1);
	len = ft_strlen(node.buff);
	write(g_fd, node.buff, len);
	ft_memdel((void**)&node.buff);
	return (len);
}
