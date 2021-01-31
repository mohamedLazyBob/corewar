/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:38:57 by mesafi            #+#    #+#             */
/*   Updated: 2020/12/24 11:38:58 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H

/*
 ** Definitions
*/

# define DLIST_H

/*
 ** Includes
*/

# include <stdlib.h>
# include "libft.h"

/*
 ** Structures
*/

typedef struct	s_dlist
{
	void			*content;
	size_t			size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

/*
 ** Functions ProtoType
*/

t_dlist		*new_dlist(void const *content, size_t size);

#endif