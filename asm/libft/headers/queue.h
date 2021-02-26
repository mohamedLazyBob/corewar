/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:37:20 by mesafi            #+#    #+#             */
/*   Updated: 2020/02/29 19:09:23 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H

/*
 ** Definitions
*/

# define QUEUE_H

/*
 ** Includes
*/

# include <libft.h>

/*
 ** Structures
*/

typedef struct	s_queue
{
	struct s_list	*front;
	struct s_list	*last;
	unsigned int	size;
}				t_queue;

/*
 ** Queue Functions
*/

void			init_queue(t_queue *q);
int				enqueue(t_queue *queue, void *content, size_t size);
void			*dequeue(t_queue *q);
void			free_queue(t_queue *queue);

#endif
