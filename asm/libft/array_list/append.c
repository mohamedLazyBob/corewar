/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 03:06:22 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/14 03:06:29 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"

static void		grow_size(t_array_list *arr)
{
	void	**new_list;

	new_list = (void **)malloc(sizeof(void *) * (2 * arr->len));
	ft_memcpy(new_list, arr->list, sizeof(void *) * arr->len);
	arr->len += INITIAL_CAPACITY;
	free(arr->list);
	arr->list = new_list;
}

void			append(t_array_list *arr, void *p)
{
	if (arr->list == NULL || p == NULL)
		return ;
	arr->cursor += 1;
	if (arr->cursor == arr->len)
		grow_size(arr);
	arr->list[arr->cursor] = p;
}
