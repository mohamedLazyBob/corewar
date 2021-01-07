/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 12:12:45 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

t_input_data		*g_input_bloc;
t_process			*g_procs_head;
unsigned int		g_last_live;
// int					g_zjmp;

/*
*******************************************************************************
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

void ft_check_size_players(t_input_data *bloc)
{
	int	i;

	i = -1;
	// while (++i <= bloc->players_counter)// it was like this, but it's an error.
	while (++i < bloc->players_counter)
	{
		if (CHAMP_MAX_SIZE < bloc->players[i].header.prog_size)
		{
			//creat somthing like dprintf
			// dprintf(2, "player_counter = %d, i = %d\n", bloc->players_counter, i);
			dprintf(2, "Error: File %s has too large a code (%u bytes > 682 bytes)\n", bloc->players[i].header.prog_name, bloc->players[i].header.prog_size);
			//ft_exit(2, bloc->playrs[i]);
			exit(1);
		}
	}
}

/*
*******************************************************************************
** we'll remove this function afterword, it's just for test purpose
*/
#if 0
void	print_input(t_input_data *bloc, int *nbr_cycles)
{
	int				idx;

	idx = 0;
	printf("dump -- type: %d, value : %d\n", nbr_cycles[0], nbr_cycles[1]);
	while (idx < bloc->players_counter)
	{
		printf("id: %d, name: [%s]\n", bloc->ids[idx], bloc->names[idx]);
		idx++;
	}
}
#endif
/*
*******************************************************************************
*/
#if 0
void	ft_temp(t_input_data bloc, t_playrs *playrs)
{
	t_process process;

		process.arena[0] = ft_init_arena(bloc, playrs);
	ft_memset(process.regestries, 0, 16*sizeof(int));

	process.player_id = bloc.ids[1];// 2
	process.regestries[1] = -process.player_id;
	//printf("{{%.8x}}\n", process.regestries[1]);

	process.pc = 1;
	process.next_inst = process.arena[0][0] - 1;
	process.carry = 1;

	process.players_counter = bloc.players_counter;

	printf("\n\n\n\n");
	//printf("next inst : %.2d\n", process.next_inst);
	for (int idx = 0; idx < 100; idx++)
		printf("%.2x ", process.arena[0][idx]);
	//ft_operation_and(&process);
	//ft_operation_zjmp(&process);
	printf("\n*****%d***%d***%d******\n", process.regestries[3], process.regestries[6], process.regestries[3]);
	ft_operation_st(&process);
	printf("\n*****%d***%d***%d******\n", process.regestries[3], process.regestries[6], process.regestries[3]);
	 printf("\n*****%d***\n", process.pc);
	for (int i = 0; i < REG_NUMBER; i++)
		printf("%d ", process.regestries[i]);
	printf("\n");
}
#endif

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
		ft_printf("* Player %d, weighing %.2d bytes, \"%s\" (\"%s\") !\n", i, \
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

static void	*battle_start(void *data)
{
	t_datum		*datum;

	datum = (t_datum *)data;
	ft_play_battle(datum->deque, &datum->procs, datum->bloc);
	return (NULL);
}

int		main(int ac, char **av)
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
	data.bloc->players = (t_playrs*)ft_memalloc(sizeof(t_playrs) * data.bloc->players_counter);
	ft_open_champion(*(data.bloc), data.bloc->players);
  	ft_check_size_players(data.bloc);
	ft_init_procs_arena(&data.procs, data.bloc);	
	ft_introduce_players(data.bloc);
	init_deque(data.deque);
	pthread_create(&thread_id, NULL, battle_start, &data);
	visualizer(data.deque);
	pthread_join(thread_id, NULL);
	ft_printf("Contestant %d, \"%s\", has won !\n", g_last_live, data.bloc->players[g_last_live - 1].header.prog_name);
	return (0);
}
