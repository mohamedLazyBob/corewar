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

void	ft_int_to_str(int var, char *str)
{
	str[3] = (unsigned int)(var);
	str[2] = (unsigned int)(var & 0x0000ff00) >> 8;
	str[1] = (unsigned int)(var & 0x00ff0000) >> 16;
	str[0] = (unsigned int)(var & 0xff000000) >> 24;
}

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
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			// return ;
	}
	else
	{
	args[0] = ft_parse_args(proc, parameters[0]);
	args[1] = ft_parse_args(proc, parameters[1]);
	if (args[1] < 1 || 16 < args[1])
		return;
	args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
	proc->carry = (args[0] == 0) ? 1 : 0;
	proc->regestries[args[1] - 1] = args[0];
	// ft_printf("the reg[%d] == %d\n", args[1] - 1, args[0]);
	mz_print_op(proc, parameters, args);
// // // 
// // 	ft_printf("at the end of ld regs value: \n");
// 	for (int i = 0; i < REG_NUMBER; i++)
// 		ft_printf("[%d] ", proc->regestries[i]);
// 	ft_printf("\n");
	}
	mz_print_pc_movements(proc);
}

/*
******************************************************************************
*/

void	ft_operation_lld(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	ft_memset(args, 0, 3);
	ft_memset(parameters, 0, 3);
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	}
	else
	{
	args[0] = ft_parse_args(proc, parameters[0]);
	args[1] = ft_parse_args(proc, parameters[1]);
	if (args[1] < 1 || 16 < args[1])
		return;
	args[0] = ft_get_argument_value_war(proc, args[0], parameters[0]);
	proc->carry = (args[0] == 0) ? 1 : 0;
	proc->regestries[args[1] - 1] = args[0];
	mz_print_op(proc, parameters, args);
	}
	mz_print_pc_movements(proc);
}

/*
******************************************************************************
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				value[3];
	int				temp;
	int             add_to_pc;
	char			str[4];
	temp = 0;
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + 
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	}
	else
	{

	value[0] = ft_parse_args(proc, parameters[0]);
	value[1] = ft_parse_args(proc, parameters[1]);
	value[2] = ft_parse_args(proc, parameters[2]);

	if (((parameters[0] == T_REG) && (value[0] < 1 || 16 < value[0])) || \
		((parameters[1] == T_REG) && (value[1] < 1 || 16 < value[1])) || \
		((parameters[2] == T_REG) && (value[2] < 1 || 16 < value[2])))
		return;

	value[0] = ft_get_argument_value_war(proc, value[0], parameters[0]);
	value[1] = ft_get_argument_value_war(proc, value[1], parameters[1]);
	ft_memcpy(&temp, proc->arena[0] + proc->op_pc + ((value[0] + value[1]) % IDX_MOD), 4);// reading the value from ram
	temp = ft_reverse_endianness((unsigned char*)&temp, 4); // revering from big_endien to small_endian
	proc->regestries[value[2] - 1] = temp;// storing the result to the 3dr argument.	
	proc->carry = (temp == 0) ? 1 : 0; // modify the carry.
	mz_print_op(proc, parameters, value);
	}
	mz_print_pc_movements(proc);
}

/*
******************************************************************************
*/

void	ft_operation_lldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				value[3];
	int				temp;
	int             add_to_pc;
	char			str[4];
	temp = 0;
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + 
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	}
	else
	{

	
	value[0] = ft_parse_args(proc, parameters[0]);
	value[1] = ft_parse_args(proc, parameters[1]);
	value[2] = ft_parse_args(proc, parameters[2]);

	if (((parameters[0] == T_REG) && (value[0] < 1 || 16 < value[0])) || \
		((parameters[1] == T_REG) && (value[1] < 1 || 16 < value[1])) || \
		((parameters[2] == T_REG) && (value[2] < 1 || 16 < value[2])))
		return;

	value[0] = ft_get_argument_value_war(proc, value[0], parameters[0]);
	value[1] = ft_get_argument_value_war(proc, value[1], parameters[1]);
	ft_memcpy(&temp, proc->arena[0] + proc->op_pc + ((value[0] + value[1])), 4);// reading the value from ram
	temp = ft_reverse_endianness((unsigned char*)&temp, 4); // revering from big_endien to small_endian
	proc->regestries[value[2] - 1] = temp;// storing the result to the 3dr argument.	
	proc->carry = (temp == 0) ? 1 : 0; // modify the carry.
	mz_print_op(proc, parameters, value);
	}
	mz_print_pc_movements(proc);
}

/*
******************************************************************************
*/
