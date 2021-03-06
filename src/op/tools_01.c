/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:55:39 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 10:57:04 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_op g_op_tab[17];

/*
********************************************************************************
** we check if args[x] == 0, so that we don't a negative number in bit[x]
** bcs when args[x] == 0, the operations doesn't have that param
** args can get these values : 1 or 2 or 3 (decimal numbers)
** 1 << bitx to check if that exact bit is activeted,
** 		means that argument is valid
** the if statement, checkt if there is a false parameter,
** 		one that the operation doesn't accept.
** the loop at the end, to validate that no parameter is missing
** (1100 0000) == 192 == 0xc0
** (0011 0000) == 48  == 0x30
** (0000 1100) == 12  == 0x0c
** it only parses the memory/arena, reads it and validate it.
*/

void	ft_get_args_type(t_process *process, unsigned char types_byte, \
								unsigned char *args)
{
	int				i;
	unsigned char	bit[3];

	args[0] = (types_byte & 192) >> 6;
	args[1] = (types_byte & 48) >> 4;
	args[2] = (types_byte & 12) >> 2;
	i = -1;
	while (++i < 3)
	{
		(args[i] == 0) ? (bit[i] = 0) : \
							(bit[i] = (unsigned char)(1 << (args[i] - 1)));
	}
	if (!(((bit[0] & g_op_tab[process->next_inst].args_type[0]) == bit[0]) && \
		((bit[1] & g_op_tab[process->next_inst].args_type[1]) == bit[1]) && \
		((bit[2] & g_op_tab[process->next_inst].args_type[2]) == bit[2])))
		ft_memcpy(args, "ER", 3);
	i = -1;
	while (++i < 3)
		if (bit[i] == 0 && g_op_tab[process->next_inst].args_type[i] != 0)
		{
			ft_memcpy(args, "ER", 3);
			break ;
		}
	process->pc = (process->pc + 1) % MEM_SIZE;
}

/*
** *****************************************************************************
** this func read from memory 1, 2 or 4 bytes depend on the type of argumet
** we get, and the size of T_DIR of the operation
** for 'par' the the only bits working in it, are the 2 first bits.
*/

int		ft_parse_args(t_process *process, unsigned char par)
{
	int	num;
	int	dir_size;

	num = 0;
	if (par == REG_CODE)
	{
		num = (int)process->arena[0][process->pc];
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else if (par == DIR_CODE)
	{
		dir_size = (g_op_tab[process->next_inst].t_dir_size ? 2 : 4);
		copy_from_arena((char*)&(num) + 4 - dir_size, \
						process->arena[0], process->pc, dir_size);
		num = ft_reverse_endianness((unsigned char*)&num, 4);
		num = (dir_size == 2) ? (short int)num : num;
		process->pc = (process->pc + dir_size) % MEM_SIZE;
	}
	else if (par == IND_CODE)
	{
		copy_from_arena((void*)&(num), process->arena[0], process->pc, 2);
		num = (short int)ft_reverse_endianness((unsigned char*)&num, 2);
		process->pc = (process->pc + 2) % MEM_SIZE;
	}
	return (num);
}

/*
******************************************************************************
** this reads from a regestrie or from a ram/arena[0] adrress
*/

int		ft_get_argument_value(t_process *process, \
										int arg, \
										unsigned char parameter)
{
	if (parameter == REG_CODE)
		arg = process->regestries[arg - 1];
	else if (parameter == IND_CODE)
	{
		copy_from_arena((void*)&arg, process->arena[0], \
						process->op_pc + (arg % IDX_MOD), 4);
		arg = ft_reverse_endianness((unsigned char*)&arg, 4);
	}
	return (arg);
}

/*
******************************************************************************
** this is the same as ft_get_argument_value, the only diff is that it's
** without the restriction of IDX_MOD
** the only operations that uses this are: ldi, and lldi;
*/

int		ft_get_argument_value_war(t_process *process, \
										int arg, \
										unsigned char parameter)
{
	int	temp;

	temp = 0;
	if (parameter == REG_CODE)
		arg = process->regestries[arg - 1];
	else if (parameter == IND_CODE)
	{
		copy_from_arena(((char*)&temp), process->arena[0], \
						process->op_pc + arg, 4);
		arg = ft_reverse_endianness((unsigned char*)&temp, 4);
	}
	return (arg);
}

/*
******************************************************************************
** this function calculates the number of bytes that we should jump over
** when the types byte isn't valid.
*/

int		mz_size_to_escape(t_process *proc)
{
	char				types_byte;
	int					ret;
	int					i;
	int					var;
	unsigned char		*par;

	i = -1;
	ret = 0;
	par = (unsigned char[3]){0, 0, 0};
	var = g_op_tab[proc->next_inst].args_num;
	types_byte = proc->arena[0][proc->op_pc + 1];
	par[0] = ((types_byte >> 6) & 3);
	par[1] = ((types_byte >> 4) & 3);
	par[2] = ((types_byte >> 2) & 3);
	while (++i < var)
	{
		if (par[i] == REG_CODE)
			ret += 1;
		else if (par[i] == IND_CODE)
			ret += 2;
		else if (par[i] == DIR_CODE)
			ret += (g_op_tab[proc->next_inst].t_dir_size ? 2 : 4);
	}
	return (ret);
}
