/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chek.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:23:56 by del-alj           #+#    #+#             */
/*   Updated: 2020/12/01 09:24:51 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

static  int ft_chek_carriage(t_process *carriage, t_game *game_params)
{
    if (game_params->cycles_to_die <= 0 || carriage->process_live <= 0)
        return (0);
    return (1);
}

static void ft_chek_cycle(t_game *game_params)
{
    if (game_params->total_live_counter >= NBR_LIVE || game_params->checks_counter == MAX_CHECKS)
        game_params->checks_counter = 0;
    game_params->cycles_to_die -= CYCLE_DELTA;
    game_params->checks_counter++;
    game_params->total_cycles_counter += game_params->cycles_to_die;
    game_params->total_live_counter = 0;
}


static void ft_kill_carriage(t_process **carriage)
{
    t_process *temp;

   if ((*carriage)->next->next == NULL)
    {
        free((*carriage)->next);
        (*carriage)->next = NULL;
    }
    else
    {
        temp = (*carriage);
        temp->next = (*carriage)->next->next;
        (*carriage) = (*carriage)->next->next;
        (*carriage) = temp;
    }
}

void        ft_chek(t_process **proc, t_game **game_params)
{
    t_process *carriage;

    carriage = *proc;
    if (carriage != NULL && carriage->next == NULL && (!(ft_chek_carriage(carriage, (*game_params)))))
    {
        free((*proc));
        (*proc) = NULL;
        (proc) = NULL;
        (carriage) = NULL;
    }
    else if (carriage != NULL && carriage->next != NULL && (!(ft_chek_carriage(carriage, (*game_params)))))
    {
        (carriage) = (carriage)->next;
        free(*proc);
        (*proc) = (carriage);
    }
    while (carriage != NULL)
    {
        if (!(ft_chek_carriage(carriage, (*game_params))))
            ft_kill_carriage(&carriage); /* ft_kill_carriage point to the next*/
        else
            carriage = carriage->next;
    }
    ft_chek_cycle((*game_params));
}
