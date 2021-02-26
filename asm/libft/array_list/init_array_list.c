/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_array_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 03:06:14 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/14 03:06:38 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_list.h"

void			init_array_list(t_array_list *arr)
{
	arr->list = (void **)malloc(sizeof(void *) * INITIAL_CAPACITY);
	arr->len = INITIAL_CAPACITY;
	arr->cursor = -1;
}
