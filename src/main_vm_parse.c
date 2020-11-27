/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/27 11:01:51 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
*******************************************************************************
** we'll remove this function afterword, it's just for test purpose
*/

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

/*
*******************************************************************************
*/

void	ft_temp(t_input_data bloc, t_playrs *playrs)
{
	t_process process;

	process.arena = ft_init_arena(bloc, playrs);
	ft_memset(process.regestries, 0, 16*sizeof(int));

	process.player_id = bloc.ids[1];// 2
	process.regestries[1] = -process.player_id;
	//printf("{{%.8x}}\n", process.regestries[1]);

	process.pc = 1;
	process.next_inst = process.arena[0] - 1;
	process.carry = 1;
	process.players_counter = bloc.players_counter;
	
	printf("\n\n\n\n");
	//printf("next inst : %.2d\n", process.next_inst);
	for (int idx = 0; idx < 100; idx++)
		printf("%.2x ", process.arena[idx]);
	//ft_operation_and(&process);
	//ft_operation_zjmp(&process);
	process.player_id = bloc.ids[3];// 4
	printf("\n*****%d***%d***%d******\n", process.regestries[3], process.regestries[6], process.regestries[3]);
	ft_operation_add(&process);
	printf("\n*****%d***%d***%d******\n", process.regestries[3], process.regestries[6], process.regestries[3]);
	 printf("\n*****%d***\n", process.pc);
//	ft_operation_st(&process);
//	ft_operation_ld(&process);
//	ft_operation_ld(&process);
//	ft_operation_add(&process);
//	ft_operation_ldi(&process);
//	ft_operation_sti(&process);
//	ft_operation_add(&process);
//	ft_operation_sub(&process);
//	ft_operation_ld(&process);
//	ft_operation_sub(&process);
//	ft_operation_ld(&process);
//	ft_operation_lld(&process);
//	ft_operation_ldi(&process);
//	ft_operation_lldi(&process);
//	ft_operation_st(&process);
//	ft_operation_sti(&process);
	printf("\n");
	for (int idx = 0; idx < 100; idx++)
		printf("%.2x ", process.arena[idx]);

	printf("\n\n\n\n");
	for (int i = 0; i < 16; i++)
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
	int				ret;
	t_header		data;
	t_playrs		*playrs;

	ft_memset(&bloc, 0, sizeof(bloc));
	ft_memset(bloc.nbr_cycles, -1, 2 * sizeof(int));
	ret = ft_read_players(ac, av, &bloc);
	if (ret == 1)
		printf("wrong number of arguments\n");
	else if (ret == 2)
		printf("wrong number in ID values \n");
	else
	{
		print_input(&(bloc), bloc.nbr_cycles);
		playrs = (t_playrs*)ft_memalloc(sizeof(t_playrs) * bloc.players_counter);
		ft_open_champion(bloc, playrs);
	//	ft_init_arena(bloc, playrs);
		ft_temp(bloc, playrs);
	}
	return (0);
}
