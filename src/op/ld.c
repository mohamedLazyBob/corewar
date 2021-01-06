/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_ld.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:42:14 by del-alj           #+#    #+#             */
/*   Updated: 2020/12/07 09:42:19 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

extern t_input_data *g_input_bloc;
extern int	g_zjmp;


/*
******************************************************************************
*/

void	ft_operation_ld(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	ft_memset(args, 0, 3);
	ft_memset(parameters, 0, 3);
	proc->op_pc = proc->pc - 1;

	// g_zjmp = 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	// som time need to prent some time not
		g_zjmp = 1;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		if (args[1] < 1 || 16 < args[1])
			return;
		// ft_printf("debug -- arg 0: %d\n", args[0]);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		// ft_printf("debug -- arg 0: %d\n", args[0]);
		proc->carry = (args[0] == 0) ? 1 : 0;
		proc->regestries[args[1] - 1] = args[0];
		mz_print_op(proc, parameters, args);
	}
	mz_print_pc_movements(proc);
	g_zjmp = 1;
	// ft_printf("im ld\n");
}
