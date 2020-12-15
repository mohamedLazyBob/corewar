/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_mini_dragon4_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:04:33 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/31 22:17:34 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/float_bigint.h"

static int		ft_loop(char *buff, char **buff_cur)
{
	while (TRUE)
	{
		if (buff == *buff_cur)
		{
			**buff_cur = '1';
			return (1);
		}
		if (*(--(*buff_cur)) != '9')
		{
			**buff_cur += 1;
			break ;
		}
	}
	return (0);
}

t_int32			ft_round_thatshit(t_bigint_compound *compound, char *buff,\
		char **cur, t_uint32 out_number)
{
	t_int32	value;
	char	*buff_cur;
	t_int32	bol;

	value = ft_bigint_compare(compound->v_num, compound->v_dom);
	buff_cur = *cur;
	(value == 0) ? (value = ((out_number & 1) == 1)) : 1;
	if (value > 0 && (out_number == 9))
	{
		bol = ft_loop(buff, &buff_cur);
		if (bol == 1)
			return (1);
	}
	else
		*buff_cur = (out_number + ((value > 0) ? '1' : '0'));
	*cur = buff_cur;
	return (0);
}
