/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:41:32 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:29:19 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		ft_putxnbr(va_list ap, int flags, int precision, int width)
{
	char					*s;
	char					*ret;
	int						i;
	unsigned long long		n;
	unsigned long long		tmp;

	i = flag_lookup(flags, LLONG, 4);
	n = (i != -1) ? (g_fetch_by_sizem[i](ap, 0)) : va_arg(ap, unsigned int);
	s = "0123456789abcdef";
	tmp = n;
	i = 0;
	while (tmp && ++i)
		tmp /= 16;
	if (n == 0)
		ret = ft_strdup("0");
	if (n && !(ret = ft_strnew(i)))
		return (0);
	while (n)
	{
		ret[i-- - 1] = s[n % 16];
		n /= 16;
	}
	set_flag_on(&flags, HEX);
	ret = build_result(flags, ret, precision, width);
	return (ft_putxstr(ret));
}

int		ft_putbxnbr(va_list ap, int flags, int precision, int width)
{
	char					*s;
	char					*ret;
	int						i;
	unsigned long long		n;
	unsigned long long		tmp;

	i = flag_lookup(flags, LLONG, 4);
	n = (i != -1) ? (g_fetch_by_sizem[i](ap, 0)) : va_arg(ap, unsigned int);
	s = "0123456789ABCDEF";
	tmp = n;
	i = 0;
	while (tmp && ++i)
		tmp /= 16;
	if (n == 0)
		ret = ft_strdup("0");
	if (n && !(ret = ft_strnew(i)))
		return (0);
	while (n)
	{
		ret[i-- - 1] = s[n % 16];
		n /= 16;
	}
	set_flag_on(&flags, BHEX);
	ret = build_result(flags, ret, precision, width);
	return (ft_putxstr(ret));
}
