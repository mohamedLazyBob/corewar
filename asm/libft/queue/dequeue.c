/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:28:29 by mesafi            #+#    #+#             */
/*   Updated: 2021/02/20 00:17:53 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void		*dequeue(t_queue *queue)
{
	t_list	*tmp;
	void	*content;

	if (queue->front == NULL)
		return (NULL);
	queue->size -= 1;
	tmp = queue->front;
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->last = NULL;
	content = tmp->content;
	ft_memdel((void **)&tmp);
	return (content);
}
