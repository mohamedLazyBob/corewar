/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:14:10 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/25 14:52:14 by del-alj          ###   ########.fr       */
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
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
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

	types_byte = proc->arena[++proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc->regestries[proc->arena[proc->pc + 3]] = \
	proc->regestries[proc->arena[proc->pc + 1]] + \
	proc->regestries[proc->arena[proc->pc + 2]];
	proc->carry = (proc->regestries[proc->arena[proc->pc + 3]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/

void	ft_operation_sub(t_process *proc)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = proc->arena[++proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc->regestries[proc->arena[proc->pc + 3]] = \
	proc->regestries[proc->arena[proc->pc + 1]] - \
	proc->regestries[proc->arena[proc->pc + 2]];
	proc->carry = (proc->regestries[proc->arena[proc->pc + 3]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/
void	ft_int_to_str(int var, char *str)
{
	str[3] = (char)(var & 0x000000ff);
	str[2] = (char)(var & 0x0000ff00) >> 8;
	str[1] = (char)(var & 0x00ff0000) >> 16;
	str[0] = (char)(var & 0xff000000) >> 24;
	printf("\n[%.8x]\n",var);
	printf("--%x %x %x %x--\n", str[0], str[1], str[2], str[3]);
}

void	ft_operation_st(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

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
		int var = 0;
		ft_memcpy(((unsigned char*)&var) + 2,proc->arena + (proc->pc + 1), 2);
		var = ft_convert_num((unsigned char*)&var, 4);

		temp = proc->pc + (var % IDX_MOD);
		printf(";;%d;;\n", temp);
		char str[4];
		ft_int_to_str(proc->regestries[proc->arena[proc->pc]], str);
		ft_memcpy(proc->arena + temp, \
				(const void *)str, 4);
		printf("[%d]\n", proc->arena[proc->pc]);
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

	types_byte = proc->arena[++proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[1] == T_IND)
		proc->pc = proc->pc + (ft_convert_num(proc->arena + (proc->pc + 1), 4) % \
				IDX_MOD);
	temp = proc->pc + ((proc->arena[proc->pc + 1] + proc->arena[proc->pc + 2]) %\
			IDX_MOD);
	ft_memcpy(proc->arena + temp, proc->arena + proc->pc, 2);
}
