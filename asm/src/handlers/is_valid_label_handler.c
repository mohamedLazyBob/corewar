/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_label_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:52:59 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/27 11:42:01 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

t_bool	is_valid_label_handler(char *str, char *label_char)
{
	if (*(label_char + 1) == LABEL_CHAR)
		return (FALSE);
	else
		str[label_char - str] = 0;
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		++str;
	}
	return (TRUE);
}

t_bool	is_ind_valid_label_handler(char *str)
{
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		++str;
	}
	return (TRUE);
}
