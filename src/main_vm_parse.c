/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/17 14:16:14 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"


/*
*******************************************************************************
*

void	print_input(t_input_data *bloc, int *nbr_cycles)
{
	printf("dump -- type: %d, value : %d\n", nbr_cycles[0], nbr_cycles[1]);

	int idx = 0;
	while (idx < bloc->players_counter)
	{
		printf ("id: %d, name: [%s]\n", bloc->ids[idx], bloc->names[idx]);
		idx++;
	}

}
int ft_read_players(int argc, char **av, t_input_data *bloc, int *nbr_cycles)
{
	int		idx;
	int		ret = 0;

	idx = 1;
	while (idx < argc)
	{
		if (bloc->players_counter == MAX_PLAYERS)
			return (1);
		ret = ft_read_dump(idx, av, nbr_cycles);
		if (ret == 0)
			ret = ft_read_player_numb(idx, av, bloc);
		if (ret == 0)
			ft_read_player_name(idx, av, bloc);
		idx += ret + 1;	
	}
	ret = ft_add_ids(bloc); // we need this func here;

	return (ret);
}

*
*******************************************************************************
*/

int		main(int ac, char **av)
{
	t_input_data	bloc;
	int				nbr_cycles[2];
	int				ret;
   	header_t		data;
	playrs_t		playrs;


	ft_memset(nbr_cycles, -1, 2 * sizeof(int));
	ft_memset((void*)&bloc, 0, sizeof(t_input_data));
	ret = ft_read_players(ac, av, &bloc, nbr_cycles);
	if (ret == 1)
		printf("wrong number of arguments\n");
	else if (ret == 2)
		printf("wrong number in ID values \n");
	else
	{
		//add playrs now i stock just 1 player
		print_input(&bloc, nbr_cycles);
		ft_open_champion(bloc, data, playrs);
	}
		return (0);
}
