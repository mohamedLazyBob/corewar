/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_label_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:52:59 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/23 02:59:12 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

t_bool	is_valid_label_handler(char *str)
{
	while (*str)
	{
		if (!ft_strrchr(LABEL_CHARS, *str))
			return (FALSE);
		++str;
	}
	return (TRUE);
}
