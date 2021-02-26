/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:55:05 by tbareich          #+#    #+#             */
/*   Updated: 2019/11/12 15:20:22 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static unsigned int	nb_len(unsigned long long n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char				*ft_unumtoa(unsigned long long n)
{
	char			*str;
	unsigned int	length;

	length = nb_len(n);
	if ((str = ft_strnew(length)) == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[--length] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
