/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:40:13 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	numlen(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		len;
	long	nb;

	i = 0;
	nb = n;
	len = numlen(n) - 1;
	str = ft_strnew(len + 1);
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		str[i++] = '-';
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
