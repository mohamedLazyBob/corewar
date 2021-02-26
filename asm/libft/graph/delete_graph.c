/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:19:04 by tbareich          #+#    #+#             */
/*   Updated: 2020/12/21 23:35:51 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void			delete_graph(t_graph *graph)
{
	t_node	*node;
	t_node	*next;

	while (graph->v)
	{
		node = graph->adj_list[graph->v - 1].head;
		while (node != NULL)
		{
			next = node->next;
			ft_memdel((void **)&node);
			node = next;
		}
		graph->v -= 1;
	}
	ft_memdel((void **)&(graph->adj_list));
	ft_memdel((void **)&graph);
}
