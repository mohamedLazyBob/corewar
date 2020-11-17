/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:42:03 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/17 14:53:37 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	print_input(t_input_data *bloc, int *nbr_cycles);
/*
*******************************************************************************
*/

typedef	struct s_box
{
	t_input_data	bloc;
	int				nbr_cycles[2];
	int				visu;

}				t_box;

int		main(int ac, char **av)
{
	t_box	box;
	//t_input_data	bloc;
	//int				nbr_cycles[2];
	int				ret;

	ft_memset(&box, 0, sizeof(box));
	ft_memset(&box->nbr_cycles, -1, 2 * sizeof(int));
	//ft_memset((void*)&bloc, 0, sizeof(t_input_data));
	ret = ft_read_players(ac, av, &bloc, nbr_cycles);
	if (ret == 1)
		printf("wrong number of arguments\n");
	else if (ret == 2)
		printf("wrong number in ID values \n");
	else
		print_input(&bloc, nbr_cycles);
	return (0);
}
