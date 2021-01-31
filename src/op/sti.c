/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:57:22 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 10:46:24 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_to_arena(t_process *proc, int place_memory, char *str)
{
	const int	player_id = proc->player_id & 0xFF;
	const int	var[4] = {(player_id | (player_id << 8) | \
					(player_id << 16) | (player_id << 24))};

	copy_to_arena(proc->arena[0], str, place_memory, 4);
	copy_to_arena(proc->arena[1], (void*)var, place_memory, 4);
}

/*
** *****************************************************************************
*/

void		ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				place_memory;
	char			str[4];

	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0))
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	else
	{
		ft_value_arg(parameters, args, proc, 3);
		if (ft_check_reg_args(parameters, args))
		{
			args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
			args[2] = ft_get_argument_value(proc, args[2], parameters[2]);
			mz_print_op(proc, args);
			place_memory = proc->op_pc + ((args[1] + args[2]) % IDX_MOD);
			place_memory = (place_memory + MEM_SIZE) % MEM_SIZE;
			ft_int_to_str(proc->regestries[args[0] - 1], str);
			ft_to_arena(proc, place_memory, str);
		}
	}
	mz_print_pc_movements(proc);
}
