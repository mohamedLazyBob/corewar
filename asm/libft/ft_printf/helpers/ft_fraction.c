/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:44:14 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 15:46:31 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*ft_fraction(union u_double	f_data)
{
	char			*fraction;
	int				pow;
	int				shift;
	int				exp;
	t_fast_power	last_pow;

	exp = f_data.t_long_double.exponent - 16383;
	pow = exp >= 0 ? 1 : abs(exp);
	last_pow.last = 0;
	shift = exp < 0 ? 64 : 63 - exp;
	if (!(fraction = ft_strnew(exp < 0 ? -exp - 1 : 0)))
		return (0);
	if (exp < 0)
		ft_memset(fraction, '0', -exp - 1);
	while (--shift >= 0 && ++pow)
	{
		fraction = ft_strjoin_free(fraction, "0", 1);
		if ((f_data.t_long_double.mantisa >> shift) & 1)
		{
			ft_fast_power(&last_pow, "5", pow - 1);
			fraction = ft_addition(&fraction, &(last_pow.last));
		}
	}
	ft_strdel(&(last_pow.last));
	return (fraction);
}
