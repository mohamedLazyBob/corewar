/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:53:57 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/18 14:41:33 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "virtual_machine.h"

void	print_arena(t_input_data bloc, unsigned char *arena)
{
	int	idx;

	idx = 0;
	while (idx < MEM_SIZE)
	{
		printf("%.2x ", arena[idx]);
		idx++;
		if (idx % 128 == 0)
			printf("\n");
	}
}

void	ft_init_arena(t_input_data bloc, t_playrs **players)
{
	unsigned	char	arena[MEM_SIZE];
	int		chunk;
	int		idx;
	int		jdx;

	ft_memset((void*)arena, 0, MEM_SIZE);
	chunk = MEM_SIZE / bloc.players_counter;
	idx = -1;
	jdx = 0;
	print_arena(bloc, arena);
	printf("\n\n\n");
	while (++idx < bloc.players_counter)
	{
		ft_memcpy(arena + jdx, players[idx]->exec_code, \
												players[idx]->header.prog_size);
		jdx += chunk;
	}

	print_arena(bloc, arena);
}
