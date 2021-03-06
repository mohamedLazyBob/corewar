/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:23:23 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 12:07:23 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		ft_reg_check(int reg)
{
	return ((reg < 1 || 16 < reg) ? 0 : 1);
}

/*
********************************************************************************
** *note : we should call this function : write_to_ram()
*/

void	ft_any_player(t_process *proc, int place_memory, char *str, int size)
{
	ft_int_to_str(proc->regestries[proc->arena[0][proc->op_pc] - 1], str);
	ft_printf("[%.2x][%.2x][%.2x][%.2x]\n", str[0], str[1], str[2], str[3]);
	ft_memcpy(proc->arena[0] + place_memory, (const void *)str, size);
	ft_memset(proc->arena[1] + place_memory, proc->player_id, size);
}
