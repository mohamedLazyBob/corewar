/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_fork_live.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:44:23 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/01 11:02:59 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern int g_last_live;
extern t_input_data *g_input_bloc;

/*
** ****************************************************************************
** live operation reads the regestre number, checks if it's a valid reg
** and the player number if it's a valid id, then makes that player as
** the last one alive
*/

static	void	mz_print_live(t_process *process)
{
	char			*name;

	if ((g_input_bloc->flags[VERBOS_1] != -1 && g_input_bloc->flags[VERBOS_1] & 1)\
	 || (g_input_bloc->flags[VERBOS_2] != -1 && g_input_bloc->flags[VERBOS_2] & 1))
	{
		for (int i = 0; i < g_input_bloc->players_counter; i++)
		{
			if (g_input_bloc->ids[i] == -1 * process->player_id)
			{
				name = g_input_bloc->players[i].header.prog_name;
				break;
			}
		}

		printf("Player %d (%s) is said to be alive\n", \
						-1*process->player_id, name);
	}
}

void	ft_operation_live(t_process *process)
{
	unsigned int	arg;

	//printf("I'm in Liive\n");
	arg = ft_parse_args(process, (unsigned char)DIR_CODE);
	process->process_live = 1;
	if (0 <= arg && arg <= REG_NUMBER)
	{
		//printf("I'm in Liive: registre valid : %d, reg[%d] = %d\n", arg, arg, process->regestries[arg]);
		if (1 <= process->regestries[arg] && \
				process->regestries[arg] <= process->players_counter)
			{
				g_last_live = -1 * process->regestries[arg];
				mz_print_live(process);
			}
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
