/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:18:41 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/27 12:18:46 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern	void			(*g_operation[16])(t_process *process);
extern	unsigned int	g_cycles_to_wait[16];
extern	const t_op		g_op_tab[17];
extern	t_process		*g_procs_head;

/*
** ****************************************************************************
*/

void		mz_print_debug_infos(t_input_data *bloc, t_game game_params)
{
	int	verbos;

	verbos = (bloc->flags[VERBOS_1] != 0) ? \
		bloc->flags[VERBOS_1] : bloc->flags[VERBOS_2];
	if (verbos && (verbos & 2))
	{
		ft_printf("It is now cycle %d\n", game_params.total_cycles_counter);
	}
}

/*
** ****************************************************************************
** Done!
*/

int			mz_dump_memory(t_input_data *bloc, t_process **procs, \
							t_game **game_par)
{
	t_game	game_params;

	game_params = **game_par;
	if ((bloc->flags[DUMP_32] != -1 && (game_params.total_cycles_counter == \
			(bloc->flags[DUMP_32]))) || (bloc->flags[DUMP_64] != -1 && \
			(game_params.total_cycles_counter == (bloc->flags[DUMP_64]))))
	{
		if (bloc->flags[DUMP_64] != -1)
			print_arena((*procs)->arena[0], bloc->flags[DUMP_64]);
		else
			print_arena((*procs)->arena[0], bloc->flags[DUMP_32]);
		return (1);
	}
	return (0);
}

/*
** ****************************************************************************
** Done
*/

void		mz_do_pause(t_game game_params, t_process **procs, \
						t_input_data *bloc)
{
	int	pause_value;

	pause_value = (bloc->flags[PAUSE_1] != -1) ? bloc->flags[PAUSE_1] : \
					bloc->flags[PAUSE_2];
	if (game_params.total_cycles_counter == pause_value)
		print_arena((*procs)->arena[0], 1);
}

/*
** ****************************************************************************
** mesafi well take care of it.
*/

void		mesafi_visualize(t_input_data *bloc, t_game game_params, \
							t_process **procs)
{
	(void)bloc;
	(void)game_params;
	(void)procs;
}

/*
** ****************************************************************************
*/
