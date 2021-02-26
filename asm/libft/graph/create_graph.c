/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:42:56 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/26 15:31:52 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include <stdlib.h>

t_graph		*create_graph(unsigned v)
{
	t_graph		*graph;
	unsigned	i;

	if (!(graph = (t_graph *)malloc(sizeof(t_graph))))
		return (NULL);
	graph->v = v;
	if (!(graph->adj_list = (t_vertex *)malloc(sizeof(t_vertex) * v)))
	{
		ft_memdel((void **)&graph);
		return (NULL);
	}
	i = 0;
	while (i < v)
	{
		graph->adj_list[i].head = NULL;
		++i;
	}
	return (graph);
}
