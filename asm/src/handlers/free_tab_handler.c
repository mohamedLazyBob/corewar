/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 07:21:45 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 07:22:05 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	free_tab_handler(t_line *tab)
{
	int	i;

	i = 0;
	while (tab[i].content)
	{
		ft_memdel((void **)&(tab[i].content));
		++i;
	}
	ft_memdel((void **)&tab);
}
