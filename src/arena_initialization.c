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
** ****************************************************************************
** this princs the arena in two modes 64/32 character per line
** we use it when dumping the memory!
*/

void	print_arena(unsigned char *arena, int bol)
{
	int	idx;
	int	line_index;

	idx = 0;
	line_index = 0;
	if (bol == 0)
		bol = 32;
	else
		bol = 64;
	ft_printf("0x%.4x : ", line_index);
	while (idx < MEM_SIZE)
	{
		ft_printf("%.2x ", arena[idx]);
		idx++;
		if (idx < MEM_SIZE && idx % bol == 0)
		{
			line_index += bol;
			ft_printf("\n");
			ft_printf("0x%.4x : ", line_index);
		}
	}
	ft_printf("\n");
}

/*
** ****************************************************************************
** initialize arena[0] with the executed code of the player
** and arena[1] with the player id
*/

int		ft_init_arena(t_input_data *bloc, \
						unsigned char *arena[2], \
						int idx, \
						unsigned int player_id)
{
	static int	pc;
	int			chunk;
	int			len;
	int			i;

	chunk = (int)(MEM_SIZE / bloc->players_counter);
	len = bloc->players[idx].header.prog_size;
	copy_to_arena(arena[0], bloc->players[idx].exec_code, pc, len);
	i = pc - 1;
	while (++i < pc + len)
		arena[1][i] = (unsigned char)player_id;
	pc += chunk;
	return (pc - chunk);
}
