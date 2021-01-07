/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:42 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/27 09:02:44 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque.h>

t_dlist		*get_front(t_deque *deque)
{
	t_dlist	*tmp;

	if (deque->front == NULL)
		return (NULL);
	deque->size -= 1;
	tmp = deque->front;
	deque->front = deque->front->next;
	if (deque->front == NULL)
		deque->rear = NULL;
	return (tmp);
}
