/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:53:57 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/27 11:09:00 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** this file is just for test, I think that we'll delete or unuse these
** function after. (we'll do a new structure)
*/

void			print_arena(t_input_data bloc, unsigned char *arena)
{
	int	idx;

	idx = 0;
	while (idx < MEM_SIZE)
	{
		printf("%.2x ", arena[idx]);
		idx++;
		if (idx % 64 == 0)
			printf("\n");
	}
}

unsigned char	*ft_init_arena(t_input_data bloc, t_playrs *players)
{
	unsigned	char	*arena;
	int					chunk;
	int					idx;
	int					jdx;

	arena = ft_memalloc(MEM_SIZE);
	chunk = MEM_SIZE / bloc.players_counter;
	idx = -1;
	jdx = 0;
	while (++idx < bloc.players_counter)
	{
		ft_memcpy(arena + jdx, players[idx].exec_code, \
												players[idx].header.prog_size);
		jdx += chunk;
	}
	print_arena(bloc, arena);
	return (arena);
}
