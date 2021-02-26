/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:08:41 by tbareich          #+#    #+#             */
/*   Updated: 2020/11/06 17:13:26 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int					abs(int x)
{
	return (x < 0 ? -x : x);
}

long long			ll_abs(long long x)
{
	return (x < 0 ? -x : x);
}
