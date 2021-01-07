/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_aff.c                                      :+:      :+:    :+:   */
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

static	void	mz_print_live(t_process *process, int arg)
{
	char			*name;

	if ((g_input_bloc->flags[VERBOS_1] != -1 && g_input_bloc->flags[VERBOS_1] & 1)\
	 || (g_input_bloc->flags[VERBOS_2] != -1 && g_input_bloc->flags[VERBOS_2] & 1))
	{
		for (int i = 0; i < g_input_bloc->players_counter; i++)
		{
			//if (g_input_bloc->ids[i] == -1 * process->player_id)
			if (g_input_bloc->ids[i] == arg)
			{
				name = g_input_bloc->players[i].header.prog_name;
				break;
			}
		}

		// ft_printf("Player %d (%s) is said to be alive\n", \
						-1*process->player_id, name);

		ft_printf("Player %d (%s) is said to be alive\n", arg, name);
	}
}

/*
** ****************************************************************************
*/

void	ft_operation_live(t_process *process)
{
	int	arg;

	arg = -1 * ft_parse_args(process, (unsigned char)DIR_CODE);
	process->process_live++;
	if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
		ft_printf("P %4d | live %d\n", process->proc_id, -arg);
	if (1 <= arg && arg <= g_input_bloc->players_counter)
	{
		g_last_live = arg;
		// process->said_live_at = ;
		mz_print_live(process, arg);
	}
	mz_print_pc_movements(process);
}

