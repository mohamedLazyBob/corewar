/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:33:40 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/27 14:35:32 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

extern t_input_data *g_input_bloc;
/*
******************************************************************************
*/

int 	ft_size(int param, int t_dir_size)
{	
	if (param == REG_CODE)
		param = 1;
	else if (param == IND_CODE)
		param = 2;
	else if (param == DIR_CODE)
		param = t_dir_size;
	return (param);
}

/*
******************************************************************************
*/

void	ft_operation_add(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		mz_print_op(proc, parameters, args);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		proc->regestries[args[2] - 1] = args[0] + args[1];
		proc->carry = (proc->regestries[args[2] - 1] == 0) ? 1 : 0;
	}			
}

/*
******************************************************************************
*/

void	ft_operation_sub(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		// if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
		// {
		// 	ft_printf("P\t%d | sub r%d r%d r%d\n", proc->proc_id, \
		// 		args[0], args[1], args[2]);
		// }
		mz_print_op(proc, parameters, args);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		proc->regestries[args[2] - 1] = args[0] + args[1];
		proc->carry = (proc->regestries[args[2] - 1] == 0) ? 1 : 0;
	}
}

/*
******************************************************************************
*/

void	ft_operation_st(t_process *proc)
{
	int	args[3];
	unsigned char	parameters[3];
	char			str[4];

		// why you do this ???
	// proc->regestries[1] = proc->regestries[0];
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
//		printf("champion operation args error, AT PC= %d\n", proc->op_pc);
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])))
			return ;
		mz_print_op(proc, parameters, args);
		// ft_printf("=============%d		%d\n", proc->regestries[1], proc->regestries[args[0] - 1]);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		// ft_printf("=============%d		%d, [%u]{%x}\n", proc->regestries[1], args[0], args[0], args[0]);

		// for (int i = 0; i < REG_NUMBER; i++)
		// 	ft_printf("[%d] ", proc->regestries[i]);
		// ft_printf("\n");
		if (parameters[1] == T_REG)
			proc->regestries[args[1] - 1] = args[0];
		else // indirect choice
		{
			// im change value args[1] = (short)args[1] for work in negatif case;
			// ft_any_player(proc, (proc->op_pc + (args[1] % IDX_MOD)), str, 4);
			ft_int_to_str(args[0], str);
			int offset = ((proc->op_pc + (args[1] % IDX_MOD)) % MEM_SIZE);
			// ft_printf("old offset = %d\n", offset);
			if (offset < 0)
				offset += MEM_SIZE;
			// ft_printf("new offset = %d\n", offset);
			// ft_printf("str from st--> [%.2x][%.2x][%.2x][%.2x]\n", str[0],  str[1], str[2], str[3]);
			// ft_printf("args[0]: %d, reg2/reg[1]: %d\n", args[0], proc->regestries[1]);
			ft_memcpy(proc->arena[0] + offset, str, 4);
			ft_memset(proc->arena[1] + offset, proc->player_id, 4);
			// ft_printf("this addr {%d} should recieve recieved [%d]\n", \
			offset, args[0]);

		}
	}
}

/*
******************************************************************************
*/

void	ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				place_memory;
	char			str[4];

	proc->op_pc = proc->pc - 1;
	// ft_printf("debug -- sti got called with op_pc: %d\n", proc->op_pc);
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);

	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[0][proc->pc % MEM_SIZE]))))
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;

		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		args[2] = ft_get_argument_value(proc, args[2], parameters[2]);

		mz_print_op(proc, parameters, args);
		// if (parameters[1] == T_IND)
			// place_memory = (proc->op_pc + args[2] % IDX_MOD% MEM_SIZE);
		// else
		place_memory = proc->op_pc + ((args[1] + args[2]) % IDX_MOD);
		// ft_printf("before place_memory == %d\n", place_memory);
		place_memory = (place_memory) % MEM_SIZE;
		// ft_printf("after place_memory == %d\n", place_memory);
		// the value in  -> args[0] not the same in -> proc->arena[0][proc->op_pc]
		// args[0] ==  proc->arena[0][proc->op_pc + 2] 
		// proc->op_pc += 2;
		
		// ft_any_player(proc, place_memory, str, 4);
		//ima nzid f op_pc 2  awla ndir hadxi li ntahit -> ntih nichan args[0]
		ft_int_to_str(proc->regestries[args[0] - 1], str);
		// ft_printf("printing offset == %d , arg[0] = %d\n", place_memory, args[0]);
		if (place_memory < 0)
			place_memory = MEM_SIZE + place_memory;
		// ft_printf("printing offset == %d \n", place_memory);
		// ft_printf("sti : str == [%.2x][%.2x][%.2x][%.2x]\n", str[0], str[1], str[2], str[3]);
		// ft_printf("this addr {%#x} should recieve recieved [%d]\n", place_memory, proc->regestries[args[0] - 1]);

		ft_memcpy(proc->arena[0] + place_memory, (const void *)str, 4);
		ft_memset(proc->arena[1] + place_memory, proc->player_id, 4);
	}
}

/*
******************************************************************************
*/
