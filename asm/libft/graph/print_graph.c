/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:14:37 by mesafi            #+#    #+#             */
/*   Updated: 2020/02/26 15:09:41 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include <ft_printf.h>

void		print_graph(t_graph *graph)
{
	unsigned		i;
	t_node			*tmp;

	i = 0;
	while (i < graph->v)
	{
		tmp = graph->adj_list[i].head;
		ft_printf("{red}%u{eoc}\t", i);
		while (tmp)
		{
			ft_printf("%u", tmp->key);
			tmp = tmp->next;
			if (tmp != NULL)
				ft_printf("{blue} -> {eoc}");
		}
		ft_printf("\n");
		++i;
	}
}
