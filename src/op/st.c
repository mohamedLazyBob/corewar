/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:53:50 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/15 10:46:52 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	st_not_reg(int *args, t_process *proc)
{
	char	str[4];
	int		*tab;
	int		offset;

	ft_int_to_str(args[0], str);
	offset = ((proc->op_pc + (args[1] % IDX_MOD)) % MEM_SIZE);
	if (offset < 0)
		offset += MEM_SIZE;
	copy_to_arena(proc->arena[0], str, offset, 4);
	tab = (int[4]){proc->player_id, proc->player_id, proc->player_id, \
			proc->player_id};
	copy_to_arena(proc->arena[1], tab, offset, 4);
}

/*
** *****************************************************************************
*/

void		ft_operation_st(t_process *proc)
{
	int				args[3];
	unsigned char	parameters[3];

	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	else
	{
		ft_value_arg(parameters, args, proc, 2);
		if (!((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1]))))
		{
			mz_print_op(proc, args);
			args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
			if (parameters[1] == T_REG)
				proc->regestries[args[1] - 1] = args[0];
			else
			{
				st_not_reg(args, proc);
			}
		}
	}
	mz_print_pc_movements(proc);
}
