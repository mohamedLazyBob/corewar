/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:23:56 by del-alj           #+#    #+#             */
/*   Updated: 2020/12/07 17:11:35 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"


extern  t_process		*g_procs_head;

static  int ft_check_carriage(t_process *carriage, t_game *game_params)
{
  if (game_params->cycles_to_die <= 0 || carriage->process_live == 0 || carriage->process_live >= game_params->cycles_to_die)
    return (0);
else
    return (1);
}

/*
** ****************************************************************************
**
*/

static void ft_check_cycle(t_game *game_params)
{
    if (game_params->total_live_counter >= NBR_LIVE || game_params->checks_counter == MAX_CHECKS)
    {
        game_params->cycles_to_die -= CYCLE_DELTA;
        if (game_params->checks_counter > 0)
            ft_printf("Cycle to die is now %d\n", game_params->cycles_to_die);
        game_params->checks_counter = 0;
    }
    else 
        game_params->checks_counter++;
	if (game_params->cycles_to_die < 0)
		game_params->cycles_to_die = 1;
    game_params->total_live_counter = 0;
}

/*
** ****************************************************************************
**
*/

static void    ft_clear_lives(t_process **proc)
{
    t_process *temp;
    temp = *proc;
    while (temp)
    {
        temp->process_live = 0;
        temp = temp->next;
    }
}

/*
** ****************************************************************************
**
*/

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
        temp = (*carriage)->next;
        (*carriage)->next = (*carriage)->next->next;
        free(temp);
    }
}

/*
** ****************************************************************************
**
*/

void        ft_check(t_process **proc, t_game **game_params)
{
    t_process *carriage;

	carriage = NULL;
    if (proc && *proc)
   {
        carriage = *proc;
        if (*proc && carriage != NULL && carriage->next == NULL && \
				(!(ft_check_carriage(carriage, (*game_params)))))
        {
            free((*proc));
            (*proc) = NULL;
            (proc) = NULL;
            (carriage) = NULL;
        }
        else if (*proc && carriage != NULL && carriage->next != NULL && \
				(!(ft_check_carriage(carriage, (*game_params)))))
        {
            (carriage) = (carriage)->next;
            free(*proc);
            (*proc) = (carriage);
        }
    
        while (carriage && carriage->next != NULL)
        {
            // ft_printf("++++++++++++debug heeere\n");
            if (!(ft_check_carriage(carriage->next, (*game_params))))
                ft_kill_carriage(&carriage);
            else
                carriage = carriage->next;
        }
        // for the laste proc
        if (*proc && carriage != NULL && carriage->next == NULL && \
				(!(ft_check_carriage(carriage, (*game_params)))))
        {
            ft_printf("Contestant %d, \"name\", has won !\n", (*proc)->player_id * -1);
            free((*proc));
            (*proc) = NULL;
            (carriage) = NULL;
        }
		if (proc && (*game_params)->cycles_to_die < 0)
		{
            free((*proc));
            (*proc) = NULL;
            //(proc) = NULL;
		}

   }
    ft_check_cycle((*game_params));
    ft_clear_lives(proc);
    // debug_print_procs_list(*proc);
}
