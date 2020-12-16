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

/*
******************************************************************************
*/

int 	ft_size(int param, int t_dir_size)
{
	if (param == T_REG)
		param = 1;
	else if (param == T_IND)
		param = 2;
	else if (param == T_DIR)
		param = t_dir_size;
	return (param);
}

/*
******************************************************************************
*/

void	ft_operation_add(t_process *proc)
{
	unsigned char	parameters[3];

	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[0][(proc->pc + 3) % MEM_SIZE]) && \
		ft_reg_check(proc->arena[0][(proc->pc + 1) % MEM_SIZE]) &&  \
		ft_reg_check(proc->arena[0][(proc->pc + 2) % MEM_SIZE]))))
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	proc->regestries[proc->arena[0][(proc->pc + 3) % MEM_SIZE]] = \
	proc->regestries[proc->arena[0][(proc->pc + 1) % MEM_SIZE]] + \
	proc->regestries[proc->arena[0][(proc->pc + 2) % MEM_SIZE]];
	proc->carry = (proc->regestries[proc->arena[0][(proc->pc + 3) \
						% IDX_MOD]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/

void	ft_operation_sub(t_process *proc)
{
	unsigned char	parameters[3];

	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[0][(proc->pc + 3) % MEM_SIZE]) && \
		ft_reg_check(proc->arena[0][(proc->pc + 1) % MEM_SIZE]) &&  \
		ft_reg_check(proc->arena[0][(proc->pc + 2) % MEM_SIZE]))))
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	proc->regestries[proc->arena[0][(proc->pc + 3) % IDX_MOD]] = \
	proc->regestries[proc->arena[0][(proc->pc + 1) % IDX_MOD]] - \
	proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]];
	proc->carry = (proc->regestries[proc->arena[0][(proc->pc + 3) \
						% IDX_MOD]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/

void	ft_operation_st(t_process *proc)
{
	unsigned char	parameters[3];
	int				temp;
	int				var;
	char			str[4];

	var = 0;
	temp = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[0][proc->pc % MEM_SIZE]))))
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
	if (parameters[1] == T_REG)
	{
		if (!(ft_reg_check(proc->arena[0][(proc->pc + 1) % MEM_SIZE])))// check if 1 <= arg2_mem_value <= 16
		{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
		}
		proc->regestries[proc->arena[0][proc->pc]] = \
		proc->regestries[proc->arena[0][(proc->pc + 1) % IDX_MOD]];
	}
	else // indirect choice
	{
		ft_memcpy(((unsigned char*)&var) + 2,proc->arena[0] + ((proc->pc + 1) % MEM_SIZE), 2);
		temp = temp + (ft_reverse_endianness((unsigned char*)&var, 4) % IDX_MOD);
		// ft_int_to_str(proc->regestries[proc->arena[0][proc->pc]], str);
		// ft_memcpy(proc->arena[0] + temp, (const void *)str, 4);

		ft_any_player(proc, temp, str, 4);
	}
	proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/

void	ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				temp;
	int 			var;
	char			str[4];
	unsigned int	args[3];

	var = 0;
	temp = proc->pc - 1;
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
		// ft_printf("------------------\n");
		args[0] = ft_parse_args(proc, parameters[0]);
		// ft_printf("args 0 : %u, pc : %d\n", args[0], proc->pc);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		// ft_printf("[%d][%d][%d]\n", args[0], args[1], args[2]);
		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		args[2] = ft_get_argument_value(proc, args[2], parameters[2]);
		// mem[args[1] + args[2]] =  args[0]
		temp = args[1] + args[2];
		ft_any_player(proc, temp, str, 4);
	}
	// ft_printf("sti r%d %d %d\n pc ", args[0], args[1], args[2]);	
	
/**/
// 	if (parameters[1] == T_IND)
// 		temp = temp + (ft_reverse_endianness(proc->arena[0] + ((proc->pc + 1) % MEM_SIZE), 4) % IDX_MOD);
// 	else
// 		temp = temp + ((proc->regestries[proc->arena[0][(proc->pc + ft_size(parameters[1], 2)) % MEM_SIZE]] + \
// 						proc->regestries[proc->arena[0][(proc->pc + ft_size(parameters[2], 2)) % MEM_SIZE]]) % IDX_MOD);
// 	ft_any_player(proc, temp, str, 2);
// /**/
//	proc->pc = (proc->pc + ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/
