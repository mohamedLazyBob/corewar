/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_fork_live.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:44:23 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/27 11:15:49 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern int g_last_live;
/*
** ****************************************************************************
** live operation reads the regestre number, checks if it's a valid reg
** and the player number if it's a valid id, then makes that player as
** the last one alive
*/

void	ft_operation_live(t_process *process)
{
	unsigned int	arg;

	arg = ft_parse_args(process, (unsigned char)DIR_CODE);
	process->process_live = 1;
	if (0 <= arg && arg <= REG_NUMBER)
	{
		if (1 <= process->regestries[arg] && \
				process->regestries[arg] <= process->players_counter)
			g_last_live = process->regestries[arg];
	}
}

/*
** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at
** FIRST_ARGUMENT % IDX_MOD
*/

void	ft_operation_fork(t_process *process)
{
	return ;
}

/*
** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at
** FIRST_ARGUMENT (without the modulo)
*/

void	ft_operation_lfork(t_process *process)
{
	return ;
}

/*
** ****************************************************************************
** aff read on byte from mem, that contains the number of the regestre to print
*/

void	ft_operation_aff(t_process *process)
{
	char			var;
	unsigned int	arg;
	unsigned char	parameter[3];

	ft_get_args_type(process, process->arena[0][process->pc], parameter);
	if (ft_strcmp((char*)parameter, "ER") == 0)
	{
		printf("ERROR in aff operation: args byte.\n");
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
	{
		arg = ft_parse_args(process, parameter[0]);
		arg = ft_get_argument_value(process, arg, parameter[0]);
		var = (char)(arg % 256);
		write(1, &var, 1);
	}
}
