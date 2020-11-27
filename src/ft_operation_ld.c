/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:18 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/27 11:27:55 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

void	ft_operation_ld(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int             add_to_pc;
	
	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_DIR)
	{
		proc->regestries[proc->arena[(proc->pc + 4) % IDX_MOD]] = \
									ft_convert_num(proc->arena + proc->pc, 4);
		add_to_pc = DIR_SIZE;
	}
	else
	{
		proc->regestries[proc->arena[(proc->pc + 2) % IDX_MOD]] = temp + \
						(ft_convert_num(proc->arena + proc->pc, 2) % IDX_MOD);
		add_to_pc = IND_SIZE;
	}
	proc->carry = (proc->regestries[proc->arena[proc->pc]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + add_to_pc + 1) % IDX_MOD;
}

/*
********************************************************************************
*/

void	ft_operation_lld(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int             add_to_pc;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_DIR)
	{
		proc->regestries[proc->arena[(proc->pc + 4) % IDX_MOD]] = \
									ft_convert_num(proc->arena + proc->pc, 4);
		add_to_pc = DIR_SIZE;
	}
	else
	{
		proc->regestries[proc->arena[(proc->pc + 2) % IDX_MOD]] = temp + \
						ft_convert_num(proc->arena + proc->pc, 2);
		add_to_pc = IND_SIZE;
	}
	proc->carry = (proc->regestries[proc->arena[proc->pc++]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + add_to_pc + 1) % IDX_MOD;
}

/*
********************************************************************************
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int             add_to_pc;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_IND)
	{
		temp = temp + (ft_convert_num(proc->arena + proc->pc, 4) % IDX_MOD);
		add_to_pc = IND_SIZE;
	}
	else
	{
		temp = temp + ((ft_convert_num(proc->arena + proc->pc, size(parameters[1], 2)) +\
			ft_convert_num(proc->arena + proc->pc, size(parameters[2], 2))) % IDX_MOD);
		
	}
	proc->regestries[proc->arena[proc->pc +  size(parameters[0], 2)]] = temp;
	proc->pc = (proc->pc + add_to_pc) % IDX_MOD;
}
/*
********************************************************************************
*/

void	ft_operation_lldi(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int             add_to_pc;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_IND)
	{
		temp = temp + (ft_convert_num(proc->arena + proc->pc, 4) % IDX_MOD);
		add_to_pc = IND_SIZE;
	}
	else
	{
		temp = temp + (ft_convert_num(proc->arena + proc->pc, size(parameters[1], 2)) +\
				ft_convert_num(proc->arena + proc->pc, size(parameters[2], 2)));

	}
	proc->regestries[proc->arena[proc->pc + size(parameters[0], 2)]] = temp;
	proc->carry = (proc->regestries[proc->arena[proc->pc]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + add_to_pc) % IDX_MOD;
}


