/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putonbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:40:30 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:29:02 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		ft_putonbr(va_list ap, int flags, int precision, int width)
{
	char				*ret;
	int					i;
	unsigned long long	n;
	unsigned long long	tmp;

	i = flag_lookup(flags, LLONG, 4);
	n = (i != -1) ? (g_fetch_by_sizem[i](ap, 0)) : va_arg(ap, unsigned int);
	tmp = n;
	i = 0;
	while (tmp && ++i)
		tmp /= 8;
	if (n == 0)
		ret = ft_strdup("0");
	if (n && !(ret = ft_strnew(i)))
		return (0);
	while (n)
	{
		ret[i-- - 1] = n % 8 + '0';
		n /= 8;
	}
	set_flag_on(&flags, OCTAL);
	ret = build_result(flags, ret, precision, width);
	return (ft_putxstr(ret));
}
