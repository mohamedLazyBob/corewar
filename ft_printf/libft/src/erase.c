/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:37 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/27 09:02:38 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque.h>

void	erase(t_deque *deque)
{
	t_dlist	*node;

	while (deque->size != 0)
	{
		node = get_front(deque);
		free(node->content);
		free(node);
	}
}
