/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 09:02:30 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/27 09:02:32 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H

/*
 ** Definitions
*/

# define DEQUE_H

/*
 ** Includes
*/

# include "dlist.h"

/*
 ** Structures
*/

typedef struct	s_deque
{
	struct s_dlist	*front;
	struct s_dlist	*rear;
	unsigned int	size;
}				t_deque;

/*
 ** Deque Functions
*/

void			init_deque(t_deque *deque);
void			insert_rear(t_deque *deque, t_dlist *node);
t_dlist			*get_front(t_deque *deque);
void			erase(t_deque *deque);

#endif
