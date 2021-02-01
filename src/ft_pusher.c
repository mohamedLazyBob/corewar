/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pusher.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 08:29:54 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/01 08:29:55 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

extern int				g_last_live;
extern unsigned int		g_live[4][2];

static void	ft_dupmem(void **dst, void *src, size_t size)
{
	if (!(*dst = malloc(size)))
		exit(1);
	ft_memcpy(*dst, src, size);
}

void		pusher(t_deque *deque, t_input_data *bloc, t_game *game_params,
					t_process *procs)
{
	t_kit		kit;
	t_process	*node;

	kit.last_live = g_last_live;
	ft_memcpy(kit.live, g_live, sizeof(g_live));
	kit.bloc = bloc;
	ft_dupmem((void **)&kit.game_params, game_params, sizeof(t_game));
	ft_dupmem((void **)&kit.procs, procs, sizeof(t_process));
	ft_dupmem((void **)&kit.procs->arena[0], procs->arena[0], MEM_SIZE);
	ft_dupmem((void **)&kit.procs->arena[1], procs->arena[1], MEM_SIZE);
	node = kit.procs;
	node->next = NULL;
	while (procs->next != NULL)
	{
		ft_dupmem((void **)&node->next, procs->next, sizeof(t_process));
		node->next->arena[0] = kit.procs->arena[0];
		node->next->arena[1] = kit.procs->arena[1];
		node = node->next;
		procs = procs->next;
		node->next = NULL;
	}
	insert_rear(deque, new_dlist(&kit, sizeof(t_kit)));
}
