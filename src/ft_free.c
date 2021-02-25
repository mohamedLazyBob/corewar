/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:17:06 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/01 09:17:07 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		ft_free(t_datum *data)
{
	t_dlist		*node;
	t_kit		*kit;
	t_process	*tmp;

	free(data->bloc);
	free(data->procs);
	while (data->deque->size > 0)
	{
		node = get_front(data->deque);
		kit = (t_kit *)node->content;
		free(kit->game_params);
		while (!kit->procs)
		{
			tmp = kit->procs;
			kit->procs = kit->procs->next;
			ft_memdel((void **)&tmp->arena[0]);
			ft_memdel((void **)&tmp->arena[1]);
			free(tmp);
		}
		free(kit);
		free(node);
	}
	free(data->deque);
}
