/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 07:14:58 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/23 07:30:45 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

char	*check_file_name_handler(char *str)
{
	char	*tmp;

	tmp = ft_strrchr(str, '.');
	if (tmp == NULL)
		error("File: Invalid Extension");
	if (*(tmp + 1) != 's' || *(tmp + 2) != 0)
		error("File: Invalid Extension");
	return (tmp);
}
