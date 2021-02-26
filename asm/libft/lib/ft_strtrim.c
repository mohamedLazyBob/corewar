/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 19:36:47 by tbareich          #+#    #+#             */
/*   Updated: 2021/01/28 14:34:19 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	int		start;
	int		end;

	if (s == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (*(s + start) == '\n' || *(s + start) == '\t' || *(s + start) == ' ')
		start++;
	while (*(s + end) == '\n' || *(s + end) == '\t' || *(s + end) == ' ')
		end--;
	if (end <= start)
		return (ft_strdup(""));
	return (ft_strsub(s, start, end - start + 1));
}
