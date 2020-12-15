/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bigint_add_sub_comp.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:48:43 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/31 22:16:42 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/float_bigint.h"

/*
** ---------------------------------------------------------------------------
** lhs = lhs - rhs;
*/

void			ft_bigint_subtraction(t_bigint *lhs, t_bigint *rhs)
{
	t_uint32 index;
	t_uint64 borrow;
	t_uint64 diff;

	index = 0;
	borrow = 0;
	while (index < lhs->length)
	{
		diff = (t_uint64)lhs->tab[index] - (t_uint64)rhs->tab[index] - \
											(t_uint64)borrow;
		borrow = (diff >> 32) & 1;
		lhs->tab[index] = (t_uint32)(diff & 0xffffffff);
		index++;
	}
}

/*
** ---------------------------------------------------------------------------
*/

static t_uint64	ft_add_ints(t_uint32 *res, t_uint64 par1, \
		t_uint64 par2, t_uint64 par3)
{
	t_uint64	temp;

	temp = par1 + par2 + par3;
	*res = (temp & 0xffffffff);
	return (temp >> 32);
}

/*
** ---------------------------------------------------------------------------
*/

t_uint32		ft_assigne_left_and_right(t_bigint lhs, t_bigint rhs, \
		t_bigint *small, t_bigint *larg)
{
	if (lhs.length >= rhs.length)
	{
		*small = rhs;
		*larg = lhs;
		return (rhs.length);
	}
	else
	{
		*small = lhs;
		*larg = rhs;
		return (lhs.length);
	}
}

/*
** ---------------------------------------------------------------------------
*/

void			ft_bigint_add(t_bigint *result, t_bigint lhs, t_bigint rhs)
{
	t_uint32	index;
	t_uint32	len;
	t_uint64	cary;
	t_bigint	larg;
	t_bigint	small;

	index = 0;
	cary = 0;
	len = ft_assigne_left_and_right(lhs, rhs, &small, &larg);
	while (index < len)
	{
		cary = ft_add_ints(result->tab + index, (t_uint64)(small.tab[index]), \
				(t_uint64)(larg.tab[index]), cary);
		index++;
	}
	(lhs.length >= rhs.length) ? (len = lhs.length) : \
								(len = rhs.length);
	while (index++ < len)
		cary = ft_add_ints(result->tab + index - 1, \
				(t_uint64)(small.tab[index - 1]), 0, cary);
	if (cary != 0)
		result->tab[index++] = cary;
	result->length = index;
}

/*
** ---------------------------------------------------------------------------
** if (lhs > rhs) return  (1)
** if (lhs == rhs) return (0)
** if (lhs < rhs)  return (-1)
*/

t_int32			ft_bigint_compare(t_bigint lhs, t_bigint rhs)
{
	int leng;

	if (lhs.length > rhs.length)
		return (1);
	else if (lhs.length < rhs.length)
		return (-1);
	else
	{
		leng = lhs.length;
		while (leng)
		{
			if (lhs.tab[leng - 1] > rhs.tab[leng - 1])
				return (1);
			else if (lhs.tab[leng - 1] < rhs.tab[leng - 1])
				return (-1);
			leng--;
		}
		return (0);
	}
}
