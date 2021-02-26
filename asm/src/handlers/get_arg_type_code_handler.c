/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_type_code_handler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 07:05:34 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 07:08:57 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		get_arg_type_code_handler(int type)
{
	int		arg_code;

	arg_code = -1;
	if (type == T_REG)
		arg_code = REG_CODE;
	else if (type == T_DIR)
		arg_code = DIR_CODE;
	else if (type == T_IND)
		arg_code = IND_CODE;
	return (arg_code);
}
