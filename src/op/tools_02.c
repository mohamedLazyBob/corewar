/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:11:11 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 09:40:48 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** ***************************************************************************
** ft_size returns the size of `param` type in the ram (arena)
** meaning the size that we gonna parse to read it's value.
*/

int		ft_size(int param, int t_dir_size)
{
	if (param == REG_CODE)
		param = 1;
	else if (param == IND_CODE)
		param = 2;
	else if (param == DIR_CODE)
		param = t_dir_size;
	return (param);
}

/*
** ***************************************************************************
** converts a 4byte int buffer, to a 4byte char buffer
*/

void	ft_int_to_str(int var, char *str)
{
	str[3] = (unsigned int)(var);
	str[2] = (unsigned int)(var & 0x0000ff00) >> 8;
	str[1] = (unsigned int)(var & 0x00ff0000) >> 16;
	str[0] = (unsigned int)(var & 0xff000000) >> 24;
}

/*
** ***************************************************************************
**  copy from arena, without overflowing the arena size.
*/

void	copy_from_arena(void *dst, void *src, int idx, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		((char*)dst)[i] = ((char*)src)[(idx + i) % MEM_SIZE];
		i++;
	}
}

/*
** ***************************************************************************
**  copy to arena, without overflowing the arena size.
*/

void	copy_to_arena(void *dst, void *src, int idx, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		((char*)dst)[(idx + i) % MEM_SIZE] = ((char*)src)[i];
		i++;
	}
}

/*
** *****************************************************************************
*/

void	ft_value_arg(unsigned char *parameters, int *value, t_process *proc, \
												int nb_arg)
{
	int	i;

	i = -1;
	while (++i < nb_arg)
	{
		(value)[i] = ft_parse_args(proc, parameters[i]);
	}
}
