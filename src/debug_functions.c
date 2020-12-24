/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:11:36 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/23 17:11:38 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
*******************************************************************************
*/

void	debug_print_procs_list(t_process *procs)
{
	t_process *temp;

	temp = procs;
	ft_printf("from the start: \n\t");
	while (temp)
	{
		// ft_printf("player_id: %d, proc_id: %d, pc: %d; next = %p\n", temp->player_id, temp->proc_id, temp->pc, temp->next);
		ft_printf("[%d] -> ", temp->proc_id);
		temp = temp->next;
	}
	ft_printf("\n");

	temp = procs;
	while (temp->next)
		temp = temp->next;
	ft_printf("from the end : \n\t");
	while (temp)
	{
		// ft_printf("player_id: %d, proc_id: %d, pc: %d; next = %p\n", temp->player_id, temp->proc_id, temp->pc, temp->next);
		ft_printf("[%d] -> ", temp->proc_id);
		temp = temp->previous;
	}
	ft_printf("\n");
}

/*
*******************************************************************************
*/

void		print_procs(t_process *ptr, t_input_data *bloc)
{
	int	idx;

	while (ptr)
	{
		printf("proc id: %d\n", ptr->proc_id);
		printf("player id: %d\n", ptr->player_id);
		idx = ft_get_player_index(bloc, -1 * ptr->player_id);
		printf("player name: %s\n", bloc->names[idx]);
		printf("pc: %d\n", ptr->pc);
		printf("player counter: %d\n", ptr->players_counter);
		ptr = ptr->next;
		printf("======================\n");
	}
}

