/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_rear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:55 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/27 09:02:56 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque.h>

void	insert_rear(t_deque *deque, t_dlist *node)
{
	deque->size += 1;
	if (deque->rear == NULL)
	{
		deque->front = node;
		deque->rear = node;
		return ;
	}
	deque->rear->next = node;
	node->prev = deque->rear;
	deque->rear = node;
}
