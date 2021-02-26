/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:05:55 by tbareich          #+#    #+#             */
/*   Updated: 2019/11/12 16:01:45 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

/*
	** Definitions
*/

# define FT_PRINTF_H

/*
	** Functions
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

#endif
