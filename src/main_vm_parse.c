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
unsigned int		g_last_live = 0;
unsigned int		g_live[4][2] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
};
int					g_current_cycle = 0;

/*
** *****************************************************************************
*/

void		ft_free_exit(char *str, void **buff, size_t size)
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

void		ft_check_size_players(t_input_data *bloc)
{
	int	i;

	i = -1;
	while (++i < bloc->players_counter)
	{
		if (CHAMP_MAX_SIZE < bloc->players[i].header.prog_size)
		{
			ft_dprintf(2, "Error: File %s has too large a code (%u bytes > 682 \
			bytes)\n", \
			bloc->names[i], \
			bloc->players[i].header.prog_size);
			exit(1);
		}
	}
}

/*
*******************************************************************************
*/

void		ft_introduce_players(t_input_data *bloc)
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

static int	data_allocation(t_datum *data)
{
	if (!(data->bloc = (t_input_data *)malloc(sizeof(t_input_data))))
		return (1);
	if (!(data->procs = (t_process *)malloc(sizeof(t_process))))
	{
		ft_memdel((void **)&(data->bloc));
		return (1);
	}
	if (!(data->deque = (t_deque *)malloc(sizeof(t_deque))))
	{
		ft_memdel((void **)&(data->bloc));
		ft_memdel((void **)&(data->procs));
		return (1);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_datum			data;
	pthread_t		thread_id;

	if (data_allocation(&data) == 1)
		return (1);
	ft_memset(data.bloc, 0, sizeof(t_input_data));
	ft_memset(data.bloc->flags, 0, 11 * sizeof(int));
	ft_read_players(ac, av, data.bloc);
	g_input_bloc = data.bloc;
	g_procs_head = NULL;
	data.bloc->players = (t_playrs*)ft_memalloc(sizeof(t_playrs) * \
			data.bloc->players_counter);
	ft_open_champion(*(data.bloc), data.bloc->players);
	ft_init_procs_arena(&data.procs, data.bloc);
	ft_introduce_players(data.bloc);
	g_last_live = data.bloc->players_counter;
	init_deque(data.deque);
	pthread_create(&thread_id, NULL, battle_start, &data);
	if (data.bloc->flags[VISU_1] != 0 || data.bloc->flags[VISU_2] != 0)
		visualizer(data.deque);
	pthread_join(thread_id, NULL);
	ft_printf("Contestant %d, \"%s\", has won !\n", g_last_live, \
			data.bloc->players[g_last_live - 1].header.prog_name);
	ft_free(&data);
	return (0);
}
