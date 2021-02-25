/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:48:04 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 09:48:54 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		ft_check_reg_args(unsigned char *parameters, int *value)
{
	if (!(((parameters[0] == T_REG) && (value[0] < 1 || 16 < value[0])) || \
			((parameters[1] == T_REG) && (value[1] < 1 || 16 < value[1])) || \
			((parameters[2] == T_REG) && (value[2] < 1 || 16 < value[2]))))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
