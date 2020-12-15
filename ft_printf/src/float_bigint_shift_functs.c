/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bigint_shift_functs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:49:55 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/31 22:16:48 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/float_bigint.h"

/*
** ---------------------------------------------------------------------------
**	result = result << 32;
*/

static	void		ft_shift_bloc(t_uint32 *dstbloc, \
									t_uint32 *srcbloc, \
									t_uint32 *stopbloc)
{
	while (srcbloc >= stopbloc)
	{
		*dstbloc = *srcbloc;
		srcbloc--;
		dstbloc--;
	}
	while (dstbloc >= stopbloc)
	{
		*dstbloc = 0;
		dstbloc--;
	}
}

/*
** ---------------------------------------------------------------------------
*/

static	void		ft_shift_bits(t_uint32 *dstbloc, \
									t_uint32 *srcbloc, \
									t_uint32 *stopbloc, \
									t_uint32 shiftbits)
{
	const	t_uint32	highbits_shift = (shiftbits % 32);
	const	t_uint32	lowbits_shift = (32 - highbits_shift);
	t_uint32			highbits;
	t_uint32			lowbits;

	highbits = 0;
	lowbits = (*srcbloc) >> lowbits_shift;
	while (srcbloc > stopbloc)
	{
		*dstbloc = highbits | lowbits;
		highbits = (*srcbloc) << highbits_shift;
		srcbloc--;
		lowbits = (*srcbloc) >> lowbits_shift;
		dstbloc--;
	}
	*dstbloc = highbits | lowbits;
	*(--dstbloc) = (*srcbloc << highbits_shift);
	while (--dstbloc >= stopbloc)
		*dstbloc = 0;
}

/*
** ---------------------------------------------------------------------------
** shift bigints to the left, "shiftbits" time
** if the shift is exactly n bloc -> ft_shift_bloc
** else it's not an exact n bloc -> ft_shift_bits
** 		in this cas we can shift for more then a bloc;
*/

void				ft_bigint_shiftleft(t_bigint *result, t_uint32 shiftbits)
{
	const	t_uint32	highbits_shift = (shiftbits % 32);
	const	t_uint32	blocs_to_shift = (shiftbits / 32);
	t_uint32			*dstbloc;
	t_uint32			*srcbloc;

	srcbloc = result->tab + result->length - 1;
	dstbloc = srcbloc + blocs_to_shift;
	if (highbits_shift == 0)
	{
		ft_shift_bloc(dstbloc, srcbloc, result->tab);
		result->length += blocs_to_shift;
	}
	else
	{
		ft_shift_bits(dstbloc + 1, srcbloc, result->tab, shiftbits);
		result->length += blocs_to_shift + 1;
		if (result->tab[result->length - 1] == 0)
			result->length--;
	}
}

/*
** ---------------------------------------------------------------------------
**	you can remove ft_bzero if result is allocated with memalloc.
**	result = lhs * rhs; (bouth of them are bigints);
*/

void				ft_bigint_mult(t_bigint *result, t_bigint lhs, t_bigint rhs)
{
	t_uint32	i;
	t_uint32	j;
	t_uint64	cary;
	t_bigint	small;
	t_bigint	larg;

	ft_assigne_left_and_right(lhs, rhs, &small, &larg);
	i = 0;
	ft_bzero((void*)result->tab, (lhs.length + rhs.length) * sizeof(t_uint32));
	while (i < small.length)
	{
		j = 0;
		while (small.tab[i] != 0 && j < larg.length)
		{
			cary = (t_uint64)result->tab[i + j] + \
					(t_uint64)small.tab[i] * (t_uint64)larg.tab[j] + cary;
			result->tab[i + j] = (t_uint32)(cary & 0xffffffff);
			cary = (cary >> 32);
			j++;
		}
		(cary != 0) ? ((result->tab[i + j] = (cary & 0xffffffff))) : 1;
		i++;
	}
	((i + j > 0) && result->tab[i + j - 1] == 0) ? (result->length = i + j - 1)\
													: (result->length = i + j);
}

/*
** ---------------------------------------------------------------------------
**	result = (bigint) * (uint32);
*/

void				ft_bigint_mult_int(t_bigint *result, \
										t_bigint lhs, \
										t_uint32 rhs)
{
	t_uint64	cary;
	t_uint32	index;

	index = 0;
	cary = 0;
	while (index < result->length)
	{
		cary = (t_uint64)lhs.tab[index] * (t_uint64)rhs + cary;
		result->tab[index] = (t_uint32)(cary & 0xffffffff);
		cary = cary >> 32;
		index++;
	}
	if (cary != 0)
		result->tab[index++] = (t_uint32)cary;
	result->length = index;
}
