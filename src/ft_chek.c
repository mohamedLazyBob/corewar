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
    if (game_params->total_live_counter >= NBR_LIVE || \
                    game_params->checks_counter  + 1 == MAX_CHECKS)
    {
        game_params->cycles_to_die -= CYCLE_DELTA;
        if (game_params->checks_counter >= 0 && ((g_input_bloc->flags[VERBOS_1] & 16 || \
			g_input_bloc->flags[VERBOS_2] & 16)))
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
                                dprintf(2, "proc [%d] live %d %p \n", temp->proc_id, temp->process_live, temp->next);


        temp->process_live = 0;
        temp = temp->next;
    }
}

/*
** ****************************************************************************
**
*/

void        ft_check(t_process **proc, t_game **game_params)
{
    t_process *carriage;
    t_process *temp;

	carriage = NULL;
    temp = NULL;
    if (proc && *proc)
   {
        carriage = *proc;
        // while (carriage)
        // {
        //     dprintf(2, "contuni\n\n");

        //     if ((*game_params)->cycles_to_die <= 0 || carriage->process_live == 0)
        //     {
        //         temp = carriage;
        //         carriage = carriage->next;
        //         if (temp)
        //             {
        //                 free(temp);
        //             }
        //         continue ;
        //     }
        //     if (carriage)
        //         carriage = carriage->next;
        // }
        // last and only
        ft_kill_last(proc, game_params, &carriage, 0);
        //for all procss exapt the first
        ft_loop_kill(proc, game_params, &carriage);          
        // first have 0 live it the problem
        ft_kill_first(proc, game_params);
        // for the laste proc ever
        ft_kill_last(proc, game_params, &carriage, 1);
		if (proc && (*game_params)->cycles_to_die < 0)
		{//need more
            free((*proc));
            (*proc) = NULL;
            (proc) = NULL;
		}
   }
//    if (proc && *proc == NULL)
//         free(proc);
// dprintf(2, "oooopla\n\n");
    ft_check_cycle((*game_params));
    ft_clear_lives(proc);
    //  debug_print_procs_list(*proc);
}
