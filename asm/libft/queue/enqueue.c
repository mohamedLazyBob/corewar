/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enqueue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:06:25 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/23 09:20:53 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

int		enqueue(t_queue *queue, void *content, size_t content_size)
{
	t_list		*node;

	if ((node = ft_lstnew(content, content_size)) == 0)
		return (-1);
	queue->size += 1;
	if (queue->last == NULL)
	{
		queue->front = node;
		queue->last = node;
		return (0);
	}
	queue->last->next = node;
	queue->last = node;
	return (0);
}
