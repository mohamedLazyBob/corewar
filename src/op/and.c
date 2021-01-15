/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators_and_jmp.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:15:15 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/14 11:40:51 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
******************************************************************************
** I think this should work, I havent tested the IND
** when we print with printf, mayge we should write to stderr
** when there is an error we estimate the max size of all args,
** and we jump to that
** types_byte -> process->arena[0][process->pc];
*/

void	ft_operation_and(t_process *process)
{
	int				args[3];
	unsigned char	parameters[3];

	process->op_pc = process->pc - 1;
	ft_get_args_type(process, process->arena[0][process->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
		process->pc = (process->pc + mz_size_to_escape(process)) % MEM_SIZE;
	else
	{
		args[0] = ft_parse_args(process, parameters[0]);
		args[1] = ft_parse_args(process, parameters[1]);
		args[2] = ft_parse_args(process, parameters[2]);
		if (!((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2]))))
		{
			args[0] = ft_get_argument_value(process, args[0], parameters[0]);
			args[1] = ft_get_argument_value(process, args[1], parameters[1]);
			process->regestries[args[2] - 1] = (args[0] & args[1]);
			(process->regestries[args[2] - 1] == 0) ? (process->carry = 1) : \
												(process->carry = 0);
			mz_print_op(process, args);
		}
	}
	mz_print_pc_movements(process);
}
