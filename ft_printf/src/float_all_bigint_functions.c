/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_all_bigint_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:14:26 by mzaboub           #+#    #+#             */
/*   Updated: 2020/01/01 02:56:30 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/float_bigint.h"

/*
** ---------------------------------------------------------------------------
** bigint copy;
*/

void		ft_bigint_copy(t_bigint *dst, t_bigint *src)
{
	t_uint32	index;

	index = 0;
	dst->length = src->length;
	while (index < src->length)
	{
		dst->tab[index] = src->tab[index];
		index++;
	}
}

/*
** ---------------------------------------------------------------------------
** result = result * 10^power
*/

void		ft_bigint_power10(t_bigint *result, t_int32 power)
{
	t_int32		index;
	t_bigint	swap;

	index = 0;
	while (index < power)
	{
		ft_bigint_copy(&swap, result);
		ft_bigint_mult_int(result, swap, 10);
		index++;
	}
}

/*
** ---------------------------------------------------------------------------
**
** 				lhs = lhs / rhs and quotient is returnd;
**
** var [0] <=> product result
** var [1] <=> borrow
** var [2] <=> difference
*/

static void	ft_divid_annex(t_bigint *lhs, \
										t_bigint *rhs, \
										t_div_vars *all)
{
	while (all->index < rhs->length)
	{
		all->var[0] = (t_uint64)rhs->tab[all->index] * (t_uint64)all->q + \
											(t_uint64)all->carry;
		all->carry = all->var[0] >> 32;
		all->var[2] = (t_uint64)lhs->tab[all->index] - \
						(all->var[0] & 0xffffffff) - all->var[1];
		all->var[1] = (all->var[2] >> 32) & 1;
		lhs->tab[all->index++] = (t_uint32)(all->var[2] & 0xffffffff);
	}
}

/*
** ----------------------------------
*/

t_uint32	ft_bigint_divid(t_bigint *lhs, t_bigint *rhs)
{
	t_div_vars	all;

	if (lhs->length < rhs->length)
		return (0);
	ft_memset(&all, 0, sizeof(all));
	all.q = lhs->tab[rhs->length - 1] / (rhs->tab[rhs->length - 1] + 1);
	(all.q > 9) ? (exit(1)) : 1;
	ft_divid_annex(lhs, rhs, &all);
	while (lhs->length > 0 && lhs->tab[lhs->length - 1] == 0)
		lhs->length = (lhs->length - 1);
	if (ft_bigint_compare(*lhs, *rhs) >= 0)
	{
		ft_bigint_subtraction(lhs, rhs);
		all.q++;
	}
	while (lhs->length > 0 && lhs->tab[lhs->length - 1] == 0)
		lhs->length = (lhs->length - 1);
	return (all.q);
}

/*
** ---------------------------------------------------------------------------
*/
