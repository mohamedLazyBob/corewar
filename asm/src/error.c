/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:29:58 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 06:55:49 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	error(char *message)
{
	if (message)
		ft_dprintf(2, "Error: %s\n", message);
	else
		ft_dprintf(2, "Unexpected error - Error\n");
	exit(1);
}

void	error_row_col(char *message, int row, int col)
{
	if (message && col < 0)
		ft_dprintf(2, "[Ln %d] Error: %s\n", row, message);
	else if (message && col >= 0)
		ft_dprintf(2, "[Ln %d, Col %d] Error: %s\n", row, col, message);
	else
		ft_dprintf(2, "[Ln %d, Col %d] Unexpected error - Error\n", row, col);
	exit(1);
}
