/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:43:06 by tbareich          #+#    #+#             */
/*   Updated: 2020/12/21 23:35:25 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include <stdlib.h>

static t_node	*new_node(unsigned int key)
{
	t_node		*node;

	if ((node = (t_node *)malloc(sizeof(t_node))) == 0)
		return (0);
	node->key = key;
	node->next = NULL;
	return (node);
}

int				add_edge(t_graph *graph, unsigned int src, unsigned int dest)
{
	t_node	*node1;
	t_node	*node2;

	if ((node1 = new_node(dest)) == 0)
		return (-1);
	node1->next = graph->adj_list[src].head;
	graph->adj_list[src].head = node1;
	if ((node2 = new_node(src)) == 0)
	{
		ft_memdel((void **)&node1);
		return (-1);
	}
	node2->next = graph->adj_list[dest].head;
	graph->adj_list[dest].head = node2;
	return (0);
}
