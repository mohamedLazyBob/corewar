/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/27 11:18:29 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

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

void	ft_temp(t_input_data bloc, t_playrs *playrs)
{
	t_process process;

	process.arena = ft_init_arena(bloc, playrs);
	ft_memset(process.regestries, 0, REG_SIZE * REG_NUMBER);
	process.regestries[0] = 1;// player id
	process.pc = 1;
	process.next_inst = process.arena[0];
	process.player_id = bloc.ids[0];
	process.carry = 0;
	process.players_counter = bloc.players_counter;

	ft_operation_and(&process);
	//ft_operation_zjmp(&process);
	for (int i = 0; i < REG_NUMBER; i++)
		printf("%d ", process.regestries[i]);
	printf("\n");
}

/*
*******************************************************************************
*/

int		main(int ac, char **av)
{
	t_input_data	bloc;
	int				nbr_cycles[2];
	t_playrs		*playrs;

	ft_memset(&bloc, 0, sizeof(bloc));
	ft_memset(bloc.nbr_cycles, -1, 2 * sizeof(int));
	ft_read_players(ac, av, &bloc);
	//print_input(&(bloc), bloc.nbr_cycles);
	
	playrs = (t_playrs*)ft_memalloc(sizeof(t_playrs) * bloc.players_counter);
	ft_open_champion(bloc, playrs);

	ft_temp(bloc, playrs);
	// init processes (all of them)
	// play the game
	// announce the winner
	// exit
	
	return (0);
}
