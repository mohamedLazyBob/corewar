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

	ft_get_args_type(proc, proc->arena[proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[(proc->pc + 3) % MEM_SIZE]) && \
		ft_reg_check(proc->arena[(proc->pc + 1) % MEM_SIZE]) &&  \
		ft_reg_check(proc->arena[(proc->pc + 2) % MEM_SIZE]))))
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	proc->regestries[proc->arena[(proc->pc + 3) % MEM_SIZE]] = \
	proc->regestries[proc->arena[(proc->pc + 1) % MEM_SIZE]] + \
	proc->regestries[proc->arena[(proc->pc + 2) % MEM_SIZE]];
	proc->carry = (proc->regestries[proc->arena[(proc->pc + 3) \
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

	ft_get_args_type(proc, proc->arena[proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[(proc->pc + 3) % MEM_SIZE]) && \
		ft_reg_check(proc->arena[(proc->pc + 1) % MEM_SIZE]) &&  \
		ft_reg_check(proc->arena[(proc->pc + 2) % MEM_SIZE]))))
	{
		proc->pc = (proc->pc + \
						ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		return ;
	}
	proc->regestries[proc->arena[(proc->pc + 3) % IDX_MOD]] = \
	proc->regestries[proc->arena[(proc->pc + 1) % IDX_MOD]] - \
	proc->regestries[proc->arena[(proc->pc + 2) % IDX_MOD]];
	proc->carry = (proc->regestries[proc->arena[(proc->pc + 3) \
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
	ft_get_args_type(proc, proc->arena[proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[proc->pc % MEM_SIZE]))))
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
	if (parameters[1] == T_REG)
	{
		if (!(ft_reg_check(proc->arena[(proc->pc + 1) % MEM_SIZE])))
		{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
		}
		proc->regestries[proc->arena[proc->pc]] = \
		proc->regestries[proc->arena[(proc->pc + 1) % IDX_MOD]];
	}
	else
	{
		ft_memcpy(((unsigned char*)&var) + 2,proc->arena + ((proc->pc + 1) % MEM_SIZE), 2);
		temp = temp + (ft_reverse_endianness((unsigned char*)&var, 4) % IDX_MOD);
		ft_int_to_str(proc->regestries[proc->arena[proc->pc]], str);
		ft_memcpy(proc->arena + temp, (const void *)str, 4);
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

	var = 0;
	temp = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		(!(ft_reg_check(proc->arena[proc->pc % MEM_SIZE]))))
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
	
/**/
	if (parameters[1] == T_IND)
		temp = temp + (ft_reverse_endianness(proc->arena + ((proc->pc + 1) % MEM_SIZE), 4) % IDX_MOD);
	else
		temp = temp + ((proc->regestries[proc->arena[(proc->pc + ft_size(parameters[1], 2)) % MEM_SIZE]] + proc->regestries[proc->arena[(proc->pc + ft_size(parameters[2], 2)) % MEM_SIZE]]) % IDX_MOD);
	ft_int_to_str(proc->regestries[proc->arena[proc->pc]], str);
	ft_memcpy(proc->arena + temp, (const void *)str, 2);
/**/
	proc->pc = (proc->pc + ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/
