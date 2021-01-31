/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:46:15 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/14 11:48:35 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern int			g_last_live;
extern t_input_data *g_input_bloc;
extern unsigned int	g_live[4][2];
extern int			g_current_cycle;

/*
** ****************************************************************************
** live operation reads the regestre number, checks if it's a valid reg
** and the player number if it's a valid id, then makes that player as
** the last one alive
*/

static	void	mz_print_live(int arg)
{
	char	*name;
	int		i;

	name = NULL;
	i = -1;
	if ((g_input_bloc->flags[VERBOS_1] & 1) || \
			(g_input_bloc->flags[VERBOS_2] & 1))
	{
		while (++i < g_input_bloc->players_counter)
		{
			if (g_input_bloc->ids[i] == arg)
			{
				name = g_input_bloc->players[i].header.prog_name;
				break ;
			}
		}
		ft_printf("Player %d (%s) is said to be alive\n", arg, name);
	}
}

/*
** ****************************************************************************
*/

void			ft_operation_live(t_process *process)
{
	int	arg;

	arg = -1 * ft_parse_args(process, (unsigned char)DIR_CODE);
	process->process_live++;
	if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
		ft_printf("P %4d | live %d\n", process->proc_id, -arg);
	if (1 <= arg && arg <= g_input_bloc->players_counter)
	{
		g_last_live = arg;
		process->valid_player_live_counter++;
		mz_print_live(arg);
		g_live[arg - 1][0] += 1;
		g_live[arg - 1][1] = g_current_cycle;
	}
	mz_print_pc_movements(process);
}