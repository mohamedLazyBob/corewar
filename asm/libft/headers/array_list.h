/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:37:25 by mesafi            #+#    #+#             */
/*   Updated: 2020/03/02 17:48:50 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LIST_H

/*
 ** Definitions
*/

# define ARRAY_LIST_H

# define INITIAL_CAPACITY 20

/*
 ** Includes
*/

# include <libft.h>

/*
 ** Structures
*/

typedef struct	s_array_list
{
	void	**list;
	int		len;
	int		cursor;
}				t_array_list;

/*
 ** Array List Functions
*/

void			init_array_list(t_array_list *arr);
void			append(t_array_list *arr, void *p);

#endif
