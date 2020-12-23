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
// note : we should call this function : write_to_ram()
void    ft_any_player(t_process *proc, int place_memory, char *str, int size)
{
	// int to_del = proc->regestries[proc->arena[0][proc->pc]];
	// to_del = ft_reverse_endianness((unsigned char*)&to_del, 4);
    // ft_int_to_str(to_del, str);

    ft_int_to_str(proc->regestries[proc->arena[0][proc->op_pc] - 1], str);
	ft_memcpy(proc->arena[0] + place_memory, (const void *)str, size);
	ft_memset(proc->arena[1] + place_memory, proc->player_id, size);
}