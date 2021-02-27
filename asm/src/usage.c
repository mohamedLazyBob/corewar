/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:23:18 by tbareich          #+#    #+#             */
/*   Updated: 2021/01/28 16:50:13 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	usage(void)
{
	ft_dprintf(2, "\n  Usage: ./asm {green}[options]{eoc} <file_name>\n\n");
	ft_dprintf(2, \
	"  [ Options ] : {green}-a{eoc} --> print the binary file in the stdout.");
	ft_dprintf(2, "\n");
	ft_dprintf(2, \
	"                {green}-h {eoc}|{green} --help{eoc} --> ");
	ft_dprintf(2, "print this help man.\n\n");
	exit(1);
}
