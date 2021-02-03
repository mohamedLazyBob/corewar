/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:04:37 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/01 09:04:38 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		*battle_start(void *data)
{
	t_datum		*datum;

	datum = (t_datum *)data;
	ft_play_battle(datum->deque, &datum->procs, datum->bloc);
	return (NULL);
}
