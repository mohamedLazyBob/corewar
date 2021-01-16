/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/16 12:08:13 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

t_input_data		*g_input_bloc;
t_process			*g_procs_head;
unsigned int		g_last_live;

/*
** *****************************************************************************
*/

void	ft_free_exit(char *str, void **buff, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(buff[i]);
		i++;
	}
	ft_putendl(str);
	exit(0);
}

/*
** *****************************************************************************
*/

void	ft_check_size_players(t_input_data *bloc)
{
	int	i;

	i = -1;
	while (++i < bloc->players_counter)
	{
		if (CHAMP_MAX_SIZE < bloc->players[i].header.prog_size)
		{
			dprintf(2, "Error: File %s has too large a code (%u bytes > 682 bytes)\n", \
			bloc->names[i], \
			bloc->players[i].header.prog_size);
			exit(1);
		}
	}
}

/*
*******************************************************************************
*/

void	ft_introduce_players(t_input_data *bloc)
{
	int	i;

	i = 0;
	ft_putstr("Introducing contestants...\n");
	while (++i <= bloc->players_counter)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i, \
				bloc->players[i - 1].header.prog_size, \
				bloc->players[i - 1].header.prog_name, \
				bloc->players[i - 1].header.comment);
	}
}

/*
*******************************************************************************
*/

int		main(int ac, char **av)
{
	t_input_data	bloc;
	t_process		*procs;

	ft_memset(&bloc, 0, sizeof(bloc));
	ft_memset(bloc.flags, 0, 11 * sizeof(int));
	ft_read_players(ac, av, &bloc);
	g_input_bloc = &bloc;
	g_procs_head = NULL;
	bloc.players = (t_playrs*)ft_memalloc(sizeof(t_playrs) * \
					bloc.players_counter);
	ft_open_champion(bloc, bloc.players);
	ft_init_procs_arena(&procs, &bloc);
	ft_introduce_players(&bloc);
	g_last_live = bloc.players_counter;
	ft_play_battle(&procs, &bloc);
	ft_printf("Contestant %d, \"%s\", has won !\n", g_last_live, \
					bloc.players[g_last_live - 1].header.prog_name);
	return (0);
}
