/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:31:38 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/26 15:58:54 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	free_queue(t_queue *queue)
{
	void	*content;

	while (queue->size != 0)
	{
		content = dequeue(queue);
		ft_memdel((void **)&content);
	}
	ft_memdel((void **)&queue);
}
