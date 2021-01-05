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
t_input_data		    *g_input_bloc;

static void ft_check_cycle(t_game *game_params)
{
    // dprintf(2, "cycle to die : %.6d tlc : %.3zu cc : %d\n", \
        game_params->cycles_to_die, game_params->total_live_counter, game_params->checks_counter);
    if (game_params->total_live_counter >= NBR_LIVE || \
                    game_params->checks_counter  + 1 == MAX_CHECKS)
    {
        game_params->cycles_to_die -= CYCLE_DELTA;
        // if (((g_input_bloc->flags[VERBOS_1] & 16 || \
		// 	g_input_bloc->flags[VERBOS_2] & 16)))
            ft_printf("Cycle to die is now %d\n", game_params->cycles_to_die);
        game_params->checks_counter = 0;
       // (game_params)->total_live_counter = 0;
    }
    else
        game_params->checks_counter++;
	// if (game_params->cycles_to_die < 0)
	// 	game_params->cycles_to_die -= 1;
}

/*
** ****************************************************************************
**
*/

static void    ft_clear_lives(t_process **proc, t_game **game_params)
{
    t_process *temp;
    temp = *proc;
    while (temp)
    {
        temp->operation_live = 0; //
        temp->process_live = 0;
        temp->operation_live = 0;
        temp = temp->next;
    }
    (*game_params)->total_live_counter = 0;
    // g_procs_head = (proc && *proc) ? (*proc) : NULL;
}

/*
** ****************************************************************************
**
*/

void        ft_check(t_process **proc, t_game **game_params)
{
    t_process *carriage;
    t_process *temp;

	// carriage = *proc;
    if (proc && *proc)
   {

        while ((*proc) && 
            (
                ((*game_params)->cycles_to_die <= 0) || \
                (((*proc)->process_live == 0) && (*proc)->is_new_bol == 0)
            )
         )
        {
            temp = (*proc);
            (*proc) = (*proc)->next;
            if (*proc)
                (*proc)->previous = temp->previous;
            free(temp);
        }

        carriage = (*proc);
        while (carriage && carriage->next)
        {
            if((*game_params)->cycles_to_die <= 0 || (carriage->next->process_live == 0 && carriage->next->is_new_bol == 0))
            {
                temp = carriage->next;
                carriage->next = carriage->next->next;
                if (carriage->next != NULL)
                    carriage->next->previous = temp->previous;
                free(temp);
                continue;
            }
            carriage = carriage->next;
        }
       	// if ((*game_params)->total_cycles_counter >= 7331)
		// {
		// 	ft_printf("in check: [%d]/[%d] [%d]\n", (*game_params)->curr_life_cycle, (*game_params)->cycles_to_die, \
		// 								(*game_params)->total_cycles_counter);
		// 	exit(0);
		// }
        // g_procs_head = carriage;

    //   // last and only
    //     ft_kill_last(proc, game_params, &carriage, 0);
    //     //for all procss exapt the first
    //     ft_loop_kill(proc, game_params, &carriage);          
    //     // first have 0 live it the problem
    //     ft_kill_first(proc, game_params);
    //     // for the laste proc ever
    //     ft_kill_last(proc, game_params, &carriage, 1);
	// 	if (proc && (*game_params)->cycles_to_die < 0)
	// 	{//need more
    //         free((*proc));
    //         (*proc) = NULL;
    //         (proc) = NULL;
	// 	}

    ft_check_cycle((*game_params));
    ft_clear_lives(proc, game_params);

   }
}
