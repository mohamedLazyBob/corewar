/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 00:53:18 by fokrober          #+#    #+#             */
/*   Updated: 2020/01/01 03:38:46 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

ssize_t		ft_putxstr(char *s)
{
	ssize_t		len;

	len = ft_strlen(s);
	write(1, s, len);
	ft_memdel((void**)&s);
	return (len);
}
