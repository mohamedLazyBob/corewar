/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:39:33 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:28:53 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	extract_nbr(char **ret, int *i, long long *n)
{
	if (!*ret)
		exit(1);
	while (*n)
	{
		(*ret)[(*i)-- - 1] = (*n) % 10 + '0';
		(*n) /= 10;
	}
}

int		ft_putdnbr(va_list ap, int flags, int precision, int width)
{
	long long	n;
	long long	tmp;
	char		*ret;
	int			i;
	int			sign;

	i = flag_lookup(flags, LLONG, 4);
	n = (i != -1) ? (g_fetch_by_sizem[i](ap, 1)) : va_arg(ap, int);
	tmp = n;
	sign = n < 0;
	i = sign;
	while (tmp && ++i)
		tmp /= 10;
	if (i == 0 && !(ret = ft_strdup("0")))
		exit(1);
	if (n && !(ret = ft_strnew(i)))
		exit(1);
	n = sign ? -1 * n : n;
	if (n < 0 && !(n = 0))
		ret = ft_strdup(MAX_L);
	extract_nbr(&ret, &i, &n);
	(void)(sign && (ret[0] = '-'));
	set_flag_on(&flags, DEC);
	ret = build_result(flags, ret, precision, width);
	return (ft_putxstr(ret));
}
