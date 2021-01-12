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
    // dprintf(2, "at cycle %zu -- cycle to die : %.6d tlc : %.3zu cc : %d\n", \
        game_params->total_cycles_counter, game_params->cycles_to_die, \
        game_params->total_live_counter, game_params->checks_counter);	

    if (game_params->total_live_counter >= NBR_LIVE || \
                    game_params->checks_counter  + 1 == MAX_CHECKS)
    {
        game_params->cycles_to_die -= CYCLE_DELTA;
	    if ((g_input_bloc->flags[VERBOS_1] & 2) || (g_input_bloc->flags[VERBOS_2] & 2))
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
        temp->valid_player_live_counter = 0;
        temp->process_live = 0;
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
    t_process	*carriage;
    t_process	*temp;
	int			var;

    if (proc && *proc)
    {
        var = ((*game_params)->total_cycles_counter - (*proc)->said_live_at);
        while ((*proc) && (((*game_params)->cycles_to_die <= 0) || \
				(((*proc)->process_live == 0) && \
					((*game_params)->total_cycles_counter - (*proc)->said_live_at) >= (*game_params)->cycles_to_die)))
        {

                temp = (*proc);
                var = (*game_params)->total_cycles_counter - temp->said_live_at;
                if (g_input_bloc->flags[VERBOS_1] & 8 || g_input_bloc->flags[VERBOS_2] & 8)
                {
                    ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
                                    temp->proc_id, var, (*game_params)->cycles_to_die);
                }
                (*proc) = (*proc)->next;
                if (*proc)
                    (*proc)->previous = temp->previous;
                free(temp);
            
        }

        carriage = (*proc);
        while (carriage && carriage->next)
        {
            temp = carriage->next;
            var = (*game_params)->total_cycles_counter - temp->said_live_at;
            if((*game_params)->cycles_to_die <= 0 || \
                (carriage->next->process_live == 0 && (var >= (*game_params)->cycles_to_die)))
            {
				if (g_input_bloc->flags[VERBOS_1] & 8 || g_input_bloc->flags[VERBOS_2] & 8)
				{
					var = (*game_params)->total_cycles_counter - temp->said_live_at;
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
							temp->proc_id, var, (*game_params)->cycles_to_die);
				}
				carriage->next = carriage->next->next;
				if (carriage->next != NULL)
					carriage->next->previous = temp->previous;
				free(temp);
				continue;
            }
            carriage = carriage->next;
        }
        ft_check_cycle((*game_params));
        ft_clear_lives(proc, game_params);
   }
}
