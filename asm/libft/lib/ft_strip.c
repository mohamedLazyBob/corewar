/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <mesafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 09:10:19 by mesafi            #+#    #+#             */
/*   Updated: 2020/02/21 19:27:19 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strip(char **str, char *chars)
{
	int		i;
	int		j;

	if (!str || !(*str))
		return ;
	i = 0;
	j = ft_strlen(*str) - 1;
	while ((*str)[i] != '\0' && ft_strchr(chars, (*str)[i]) != NULL)
		++i;
	while ((*str)[j] != '\0' && ft_strchr(chars, (*str)[j]) != NULL)
		--j;
	free(*str);
	if (j < i)
		*str = ft_strdup("");
	else
		*str = ft_strsub(*str, i, j - i + 1);
}
