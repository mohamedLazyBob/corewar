/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whole.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:44:25 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 15:14:22 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*ft_whole(union u_double f_data)
{
	char			*whole;
	int				shift;
	int				pow;
	int				exp;
	t_fast_power	last_pow;

	if (!(whole = ft_strnew(1)))
		return (0);
	whole[0] = '0';
	last_pow.last = 0;
	exp = f_data.t_long_double.exponent - 16383;
	shift = exp >= 64 ? 0 : 63 - exp;
	pow = exp > 63 ? exp - 63 : 0;
	while (shift < 64 && exp >= 0)
	{
		if ((f_data.t_long_double.mantisa >> shift) & 1)
		{
			ft_fast_power(&last_pow, "2", pow);
			whole = ft_addition(&whole, &(last_pow.last));
		}
		pow++;
		shift++;
	}
	ft_strdel(&(last_pow.last));
	return (whole);
}
