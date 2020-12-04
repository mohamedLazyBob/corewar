/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:53:57 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/03 12:19:34 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** this file is just for test, I think that we'll delete or unuse these
** function after. (we'll do a new structure)
*/

void	print_arena(unsigned char *arena, int bol)
{
	int	idx;

	idx = 0;
	system("clear");
	if (bol == 0)
		bol = 32;
	else
		bol = 64;
	while (idx < MEM_SIZE)
	{
		printf("%.2x ", arena[idx]);
		idx++;
		if (idx % bol == 0)
			printf("\n");
	}
}

int		ft_init_arena(t_input_data *bloc, unsigned char *arena, int player_id)
{
	static int	pc;
	int			chunk;
	int			len;

	chunk = (int)(MEM_SIZE / bloc->players_counter);
	len = bloc->players[player_id].header.prog_size;
	ft_memcpy(arena + pc, bloc->players[player_id].exec_code, len);
	pc += chunk;
	//print_arena(bloc, arena);
	return (pc - chunk);
}
