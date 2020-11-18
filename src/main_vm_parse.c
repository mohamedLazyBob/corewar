/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/18 10:52:54 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
*******************************************************************************
** we'll remove this function afterword, it's just for test purpose
*/

void	print_input(t_input_data *bloc, int *nbr_cycles)
{
	int idx;

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

int		main(int ac, char **av)
{
	t_input_data	bloc;
	int				nbr_cycles[2];
	int				ret;

	ft_memset(&bloc, 0, sizeof(bloc));
	ft_memset(bloc.nbr_cycles, -1, 2 * sizeof(int));
	ret = ft_read_players(ac, av, &bloc);
	if (ret == 1)
		printf("wrong number of arguments\n");
	else if (ret == 2)
		printf("wrong number in ID values \n");
	else
		print_input(&(bloc), bloc.nbr_cycles);
	return (0);
}
