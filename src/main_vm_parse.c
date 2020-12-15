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

t_input_data *g_input_bloc;

/*
*******************************************************************************
*/

void	ft_free_exit(char *str, void **buff, size_t size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(buff[i]);
	ft_putendl(str);
	exit(0);
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
		/*
		putstr("* Player ");
		ft_putnbr(%d);
		ft_putstr(", weighting ");
		ft_putnbr("%.2d ");
		ft_putstr("bytes, \"");
		ft_putstr("%s\"); (\"%s\") !\n", i, \
		*/
		printf("* Player %d, weighting %.2d bytes, \"%s\" (\"%s\") !\n", i, \
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
	//int				nbr_cycles[2];
	//t_playrs		*playrs;

	ft_memset(&bloc, 0, sizeof(bloc));
	ft_memset(bloc.flags, -1, 11 * sizeof(int));
	ft_read_players(ac, av, &bloc);
	g_input_bloc = &bloc;
	
	bloc.players = (t_playrs*)ft_memalloc(sizeof(t_playrs) * bloc.players_counter);
	ft_open_champion(bloc, bloc.players);

	// init processes (all of them)
	ft_init_procs_arena(&procs, &bloc);
	//		print_procs(procs, &bloc);
	//		print_arena(bloc, procs->arena[0]);
	ft_introduce_players(&bloc);
	ft_play_battle(&procs, &bloc);
	// play the game: the loop
		// sets the opcode
		// Reduce the number of cycles before execution
		// Perform operation
		// Check if needed:tabe 
	// announce the winner
	// exit
	
	return (0);
}
