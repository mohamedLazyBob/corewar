/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:23:23 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/30 13:23:31 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

int     ft_reg_check(int reg)
{
	return ((reg < 1 || 16 < reg) ? 0 : 1);
}

/*
******************************************************************************
*/

void    ft_any_player(t_process *proc, int temp, char *str, int size)
{
    ft_int_to_str(proc->regestries[proc->arena[0][proc->pc]], str);
	ft_memcpy(proc->arena[0] + temp, (const void *)str, size);
	ft_memset(proc->arena[1] + temp, proc->player_id, size);
}