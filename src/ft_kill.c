/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:04:03 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/16 11:55:16 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

static int	ft_check_carriage(t_process *carriage, t_game *game_params)
{
	if ((game_params->cycles_to_die <= 0 || carriage->process_live == 0))
		return (0);
	else
		return (1);
}

/*
** *****************************************************************************
*/

void		ft_kill_carriage(t_process **carriage)
{
	t_process	*temp;

	if ((*carriage)->next->next == NULL)
	{
		free((*carriage)->next);
		(*carriage)->next = NULL;
	}
	else
	{
		temp = (*carriage)->next;
		(*carriage)->next = (*carriage)->next->next;
		free(temp);
	}
}

/*
** ****************************************************************************
*/

void		ft_kill_last(t_process **proc, t_game **game_params,\
							t_process **carriage, int nb)
{
	if (*proc && (*carriage) != NULL && (*carriage)->next == NULL && \
			(!(ft_check_carriage((*carriage), (*game_params)))))
	{
		if (nb == 1)
			ft_printf("Contestant %d, \"name\", has won !\n", \
					(*proc)->player_id * -1);
		(*proc)->previous = NULL;
		(*proc)->next = NULL;
		free((*proc));
		(*proc) = NULL;
		(proc) = NULL;
		(*carriage) = NULL;
	}
}

/*
** ****************************************************************************
*/

void		ft_loop_kill(t_process **proc, t_game **game_params, \
						t_process **carriage)
{
	while (*proc && (*carriage) && (*carriage)->next != NULL)
	{
		if (!(ft_check_carriage((*carriage)->next, (*game_params))))
			ft_kill_carriage(carriage);
		else
			(*carriage) = (*carriage)->next;
	}
}

/*
** ****************************************************************************
*/

void		ft_kill_first(t_process **proc, t_game **game_params)
{
	t_process	*temp;

	if ((*proc) && (!(ft_check_carriage((*proc), (*game_params)))))
	{
		temp = (*proc);
		(*proc) = (*proc)->next;
		if (*proc != NULL)
			(*proc)->previous = NULL;
		free(temp);
		temp = NULL;
	}
}
