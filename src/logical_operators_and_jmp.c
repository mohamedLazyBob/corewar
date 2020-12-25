/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators_and_jmp.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:15:15 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/03 09:30:45 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_op g_op_tab[];
unsigned int g_last_live;
extern t_input_data *g_input_bloc;

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
	int	args[3];
	unsigned char	parameters[3];

	process->op_pc = process->pc - 1;
	ft_get_args_type(process, process->arena[0][process->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		printf("champion operation args error, AT PC= %d\n", process->op_pc);
		process->pc = (process->pc + \
						ft_sizeof_params(process, parameters)) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(process, parameters[0]);
		args[1] = ft_parse_args(process, parameters[1]);
		args[2] = ft_parse_args(process, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		args[0] = ft_get_argument_value(process, args[0], parameters[0]);
		args[1] = ft_get_argument_value(process, args[1], parameters[1]);
		process->regestries[args[2] - 1] = (args[0] & args[1]);
		(process->regestries[args[2] - 1] == 0) ? (process->carry = 1) : \
											(process->carry = 0);
		mz_print_op(process, parameters, args);
	}
}

/*
** ****************************************************************************
** or is the same as and, the only diff is the operator we use
*/

void	ft_operation_or(t_process *process)
{
	// int				i;
	int	args[3];
	unsigned char	parameters[3];

	// i = -1;
	process->op_pc = process->pc - 1;
	ft_get_args_type(process, process->arena[0][process->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		printf("champion operation args error, AT PC= %d\n", process->op_pc);
		process->pc = (process->pc + REG_SIZE * 3) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(process, parameters[0]);
		args[1] = ft_parse_args(process, parameters[1]);
		args[2] = ft_parse_args(process, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		args[0] = ft_get_argument_value(process, args[0], parameters[0]);
		args[1] = ft_get_argument_value(process, args[1], parameters[1]);
		process->regestries[args[2] - 1] = (args[0] | args[1]);
		(process->regestries[args[2] - 1] == 0) ? (process->carry = 1) : \
											(process->carry = 0);
		mz_print_op(process, parameters, args);
	}
}

/*
** ****************************************************************************
** xor is the same as and, or. the only diff the operator we use
*/

void	ft_operation_xor(t_process *process)
{
	// int				i;
	int	args[3];
	unsigned char	parameters[3];

	// i = -1;
	process->op_pc = process->pc - 1;
	ft_get_args_type(process, process->arena[0][process->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
	//	printf("champion operation args error, AT PC= %d\n", process->op_pc);
		process->pc = (process->pc + REG_SIZE * 3) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(process, parameters[0]);
		args[1] = ft_parse_args(process, parameters[1]);
		args[2] = ft_parse_args(process, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		args[0] = ft_get_argument_value(process, args[0], parameters[0]);
		args[1] = ft_get_argument_value(process, args[1], parameters[1]);
		process->regestries[args[2] - 1] = (args[0] ^ args[1]);
		(process->regestries[args[2] - 1] == 0) ? (process->carry = 1) : \
											(process->carry = 0);
		mz_print_op(process, parameters, args);
	}
}

/*
** ****************************************************************************
** zjmp reads 2 bytes from the mem,
** and adds that value to pc if carry = 1;
*/

void	ft_operation_zjmp(t_process *process)
{
	short int arg1;

	process->op_pc = process->pc - 1;
	arg1 = ft_parse_args(process, (unsigned char)DIR_CODE);
	// ft_printf("\t\targ1: %d\n", arg1);
	if (process->carry == 1)
	{
		process->pc = process->op_pc + (arg1 % IDX_MOD);
		if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
			ft_printf("P    %d | zjmp %d OK\n", process->proc_id, arg1);
	}
	else
	{
		if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
			ft_printf("P    %d | zjmp %d FAILED\n", process->proc_id, arg1);
		if (g_input_bloc->flags[VERBOS_1] & 16 || g_input_bloc->flags[VERBOS_2] & 16)
			mz_print_pc_movements(process);
	}
}
