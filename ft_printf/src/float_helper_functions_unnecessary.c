/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_helper_functions_unnecessary.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:41:39 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:23:05 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int			power(int n, int i)
{
	int j;
	int res;

	j = 0;
	res = 1;
	while (j < i)
	{
		res *= n;
		j++;
	}
	return (res);
}

/*
** ****************************************************************************
*/

t_uint32	is_special_case(t_bigint_compound *compound, t_buffer *node)
{
	if (compound->bigbit == -1337 && compound->v_num.length == 0)
	{
		if (compound->sign & 1)
			ft_strcpy(node->buff, "-inf");
		else
			ft_strcpy(node->buff, "inf");
		return (TRUE);
	}
	else if (compound->bigbit == -1337 && compound->v_num.length != 0)
	{
		ft_strcpy(node->buff, "nan");
		return (TRUE);
	}
	return (FALSE);
}

/*
** *************************
*/

void		ft_special_case(t_buffer *node)
{
	set_flag_on(&(node->flags), STRING);
	set_flag_off(&(node->flags), XFLOAT);
	set_flag_off(&(node->flags), ZERO);
	node->buff = \
		build_result(node->flags, node->buff, node->precision, node->width);
}

/*
** ***************************************************************************
*/

t_uint32	ft_add_sign(t_bigint_compound *compound, t_buffer node)
{
	if (compound->sign & 1)
	{
		node.buff[0] = '-';
		return (1);
	}
	else if (is_on(node.flags, PLUS))
	{
		node.buff[0] = '+';
		return (1);
	}
	else if (is_on(node.flags, SPACE))
	{
		node.buff[0] = ' ';
		return (1);
	}
	else
		return (0);
}
