/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 00:53:18 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:29:25 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

extern	int	g_fd;

ssize_t		ft_putxstr(char *s)
{
	ssize_t		len;

	len = ft_strlen(s);
	write(g_fd, s, len);
	ft_memdel((void**)&s);
	return (len);
}
