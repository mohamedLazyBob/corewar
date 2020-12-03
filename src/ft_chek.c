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

int     ft_chek_carriage(t_process *carriage, int *cycle)
{
    if (carriage->cycle_to_die <= 0 || carriage->operation_live <= 0)
        return (0);
    if (carriage->operation_live >= NBR_LIVE || carriage->check == MAX_CHECKS)
    {
        carriage->cycle_to_die -= CYCLE_DELTA;
        carriage->check = 0;
    }
    else
    {
        /* If MAX_CHECKS after checks the value cycles_to_die does \
        not change, then it will be forcedly decreased by the value CYCLE_DELTA. */
       carriage->cycle_to_die -= CYCLE_DELTA;
    }
    carriage->operation_live = 0;
    carriage->check++;
    cycle += carriage->cycle_to_die;
    return (1);
}

void    ft_kill_carriage(t_process **carriage, t_process **proc)
{
    t_process *temp;

    if (((*carriage)->next == NULL && (*carriage)->previous == NULL)) /* the last (*carriage)*/
    {
        free((*proc));
        (*proc) = NULL;
        (proc) = NULL;
        (*carriage) = NULL;
        (carriage) = NULL;
    }
    else if ((*carriage)->next == NULL) /*last curriage in the list order*/
    {
        free((*carriage));
        (*carriage)->previous->next = NULL;
        (*carriage) = NULL;

    }
    else
    {
        
        if ((*carriage)->previous == NULL) /* the first curriage in the list order*/
        {
            (*carriage) = (*carriage)->next;
            free((*carriage)->previous);
            (*carriage)->previous = NULL;
            (*proc) = (*carriage);

        }
        else
        {
            temp = (*carriage)->previous;
            temp->next = (*carriage)->next;
            (*carriage) = (*carriage)->next;
            (*carriage)->previous = temp;
        }
    }
}

void    ft_chek(t_process **proc, int *cycle)
{
    t_process *carriage;

    carriage = *proc;
    while (carriage != NULL)
    {
        if (!(ft_chek_carriage(carriage, cycle)))
            ft_kill_carriage(&carriage, proc); /* ft_kill_carriage point to the next*/
        else
            carriage = carriage->next;
    }
}
