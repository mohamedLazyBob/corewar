/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:10:17 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 09:05:35 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	w_nb(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			++str;
		if (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
			break ;
		if (*str)
			++i;
		if (*str == DIRECT_CHAR || *str == SEPARATOR_CHAR ||
				*str == LABEL_CHAR)
		{
			++str;
			continue ;
		}
		if (*str == '-')
			++str;
		while (*str && *str != ' ' && *str != '\t' && *str != '\n' &&
				*str != COMMENT_CHAR && *str != ALT_COMMENT_CHAR
				&& *str != DIRECT_CHAR && *str != SEPARATOR_CHAR && *str != '-')
			++str;
	}
	return (i);
}

static int	next_white_space(char *str, int j)
{
	if (str[j] == '-')
		++j;
	while (str[j] != ' ' && str[j] != '\t' && str[j] != '\n' && str[j] &&
			str[j] != COMMENT_CHAR && str[j] != ALT_COMMENT_CHAR
			&& str[j] != DIRECT_CHAR && str[j] != SEPARATOR_CHAR &&
			str[j] != '-')
		++j;
	return (j);
}

static int	ignore_white_spaces(char *str, int *i, int *tabulation)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	{
		if (str[*i] == '\t')
			++(*tabulation);
		++(*i);
	}
	return ((*i) - (*tabulation) + (*tabulation) * 4 + 1);
}

static void	spliter_helper(t_line *tab, char *str, int *k)
{
	int		i;
	int		j;
	int		tabulation;

	i = 0;
	j = 0;
	tabulation = 0;
	while (str[i = j])
	{
		tab[*k].col = ignore_white_spaces(str, &i, &tabulation);
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			break ;
		j = i;
		if (str[j] == DIRECT_CHAR || str[j] == SEPARATOR_CHAR ||
			str[j] == LABEL_CHAR)
		{
			tab[(*k)++].content = ft_strsub(str + i, 0, ++j - i);
			continue ;
		}
		j = next_white_space(str, j);
		if (j != i)
			tab[(*k)++].content = ft_strsub(str + i, 0, j - i);
	}
}

t_line		*spliter(char *str)
{
	t_line	*tab;
	int		k;

	if (str == 0)
		return (0);
	if ((tab = (t_line *)ft_memalloc((w_nb((char *)str) + 1) *
			sizeof(t_line))) == 0)
		return (0);
	k = 0;
	spliter_helper(tab, str, &k);
	return (tab);
}
