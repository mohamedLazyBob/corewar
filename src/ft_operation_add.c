/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:14:10 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/26 12:10:46 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

void	ft_operation_and(t_process *process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = process->arena[process->pc + 1];
	ft_get_args_type(*process, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}
}

/*
********************************************************************************
*/

void	ft_operation_add(t_process *proc)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->regestries[proc->arena[proc->pc + 3]] = \
	proc->regestries[proc->arena[proc->pc + 1]] + \
	proc->regestries[proc->arena[proc->pc + 2]];
	proc->carry = (proc->regestries[proc->arena[proc->pc + 3]] == 0) ? 1 : 0;
	proc->pc += 3;
}

/*
********************************************************************************
*/

void	ft_operation_sub(t_process *proc)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->regestries[proc->arena[proc->pc + 3]] = \
	proc->regestries[proc->arena[proc->pc + 1]] - \
	proc->regestries[proc->arena[proc->pc + 2]];
	proc->carry = (proc->regestries[proc->arena[proc->pc + 3]] == 0) ? 1 : 0;
	proc->pc += 3;
}

/*
********************************************************************************
*/

void	ft_int_to_str(int var, char *str)
{
	str[3] = (unsigned int)(var);
	str[2] = (unsigned int)(var & 0x0000ff00) >> 8;
	str[1] = (unsigned int)(var & 0x00ff0000) >> 16;
	str[0] = (unsigned int)(var & 0xff000000) >> 24;
}

/*
********************************************************************************
*/

void	ft_operation_st(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int				var;
	char			str[4];
	
	var = 0;
	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	proc->pc++;
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	if (parameters[1] == T_REG)
	{
		proc->regestries[proc->arena[proc->pc]] = \
		proc->regestries[proc->arena[proc->pc + 1]];
		proc->pc += 2;
	}
	else
	{
		ft_memcpy(((unsigned char*)&var) + 2,proc->arena + (proc->pc + 1), 2);
		temp = temp + (ft_convert_num((unsigned char*)&var, 4) % IDX_MOD);	
		ft_int_to_str(proc->regestries[proc->arena[proc->pc]], str);
		ft_memcpy(proc->arena + temp, (const void *)str, 4);
		proc->pc += 3;
	}
}

/*
********************************************************************************
*/

void	ft_operation_sti(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;
	int 			var;
	char			str[4];

	var = 0;
	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	proc->pc++;
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	if (parameters[1] == T_IND)
		temp = temp + (ft_convert_num(proc->arena + (proc->pc + 1), 4) % \
				IDX_MOD);
	else
	{
			if (parameters[1] == T_REG && parameters[2] == T_REG)
				temp = temp + ((proc->regestries[proc->arena[proc->pc + 1]] + \
						proc->regestries[proc->arena[proc->pc + 2]]) % IDX_MOD);
			else if (parameters[1] == T_REG && parameters[2] == T_DIR)
				temp = temp + ((proc->regestries[proc->arena[proc->pc + 1]] + \
					ft_convert_num(proc->arena + (proc->pc + 2), 2)) % IDX_MOD);
			else if (parameters[1] == T_DIR && parameters[2] == T_REG)
				temp = temp + ((ft_convert_num(proc->arena + (proc->pc + 1), 2)\
					+ proc->regestries[proc->arena[proc->pc + 3]]) % IDX_MOD);
			else if (parameters[1] == T_DIR && parameters[2] == T_DIR)
				temp = temp + (ft_convert_num(proc->arena + (proc->pc + 1), 2)\
				+ (ft_convert_num(proc->arena + (proc->pc + 3), 2)) % IDX_MOD);
			else
				;
	}
	ft_int_to_str(proc->regestries[proc->arena[proc->pc]], str);
	ft_memcpy(proc->arena + temp, (const void *)str, 2);
}
