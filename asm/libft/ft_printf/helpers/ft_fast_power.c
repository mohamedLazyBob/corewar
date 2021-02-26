/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fast_power.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:36:03 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 15:50:16 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	ft_fast_power(t_fast_power *last_power, char *base, int exp)
{
	char		*result;
	int			pow;
	char		*tmp;

	if (!last_power->last)
		last_power->pow = 0;
	result = ft_strnew(1);
	base = ft_strdup(base);
	result[0] = '1';
	pow = exp - last_power->pow > 0 ? exp - last_power->pow : exp;
	while (1)
	{
		if (pow & 1)
			result = ft_multiplication(&result, &base);
		pow >>= 1;
		if (!pow)
			break ;
		base = ft_multiplication(&base, &base);
	}
	tmp = last_power->last;
	last_power->last = !last_power->last ? result :
						ft_multiplication(&result, &(last_power->last));
	ft_strdel(&tmp);
	last_power->pow = exp;
	ft_strdel(&base);
}
