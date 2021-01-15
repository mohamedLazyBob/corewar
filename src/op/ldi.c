/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:36:51 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 09:49:12 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** ****************************************************************************
** ZAZs corewar doesn't modify the carry for somereason idk.
** ldi should modify it as all the other operations and that what we do
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				value[3];
	int				temp;

	temp = 0;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	else
	{
		ft_value_arg(parameters, value, proc, 3);
		if (ft_check_reg_args(parameters, value))
		{
			value[0] = ft_get_argument_value_war(proc, value[0], parameters[0]);
			value[1] = ft_get_argument_value_war(proc, value[1], parameters[1]);
			copy_from_arena(&temp, proc->arena[0], proc->op_pc + ((value[0] + \
							value[1]) % IDX_MOD), 4);
			temp = ft_reverse_endianness((unsigned char*)&temp, 4);
			proc->regestries[value[2] - 1] = temp;
			proc->carry = (temp == 0) ? 1 : 0;
			mz_print_op(proc, value);
		}
	}
	mz_print_pc_movements(proc);
}
