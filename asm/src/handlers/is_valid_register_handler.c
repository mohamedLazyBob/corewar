/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_register_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:55:35 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/25 23:14:57 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

t_bool	is_valid_register_handler(char *str)
{
	int	value;

	if (str[0] != 'r')
		return (FALSE);
	if (str[1] > '9' || str[1] < '0')
		return (FALSE);
	if (str[2] == 0)
		return (TRUE);
	if (str[2] > '9' || str[2] < '0')
		return (FALSE);
	if (str[3] != 0)
		return (FALSE);
	value = ft_atoi(str);
	if (value > REG_NUMBER)
		error("Register: You exceeded REG_NUMBER, check op.h file.");
	return (TRUE);
}
