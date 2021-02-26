/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 04:43:04 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 19:06:31 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	player_w_nb(char *str, int qn)
{
	int		i;

	i = 0;
	while (*str)
	{
		while (qn != 1 && (*str == ' ' || *str == '\t' || *str == '\n'))
			++str;
		if (qn != 1 && (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR))
			break ;
		if (*str)
		{
			++i;
			if (*str == '"')
			{
				++str;
				qn = qn == 1 ? 0 : qn + 1;
				continue ;
			}
		}
		while (*str && (qn == 1 || (*str != ' ' && *str != '\t' &&
				*str != '\n')) && *str != '"')
			++str;
	}
	return (i);
}

static int	ignore_white_spaces(char *str, int *qn, int *i, int *tabulation)
{
	while (*qn != 1 && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
	{
		if (str[*i] == '\t')
			++(*tabulation);
		++(*i);
	}
	return ((*i) - (*tabulation) + (*tabulation) * 4 + 1);
}

static void	spliter_helper(t_line *tab, char *str, int *qn, int *k)
{
	int		i;
	int		j;
	int		tabulation;

	tabulation = 0;
	i = 0;
	j = 0;
	while (str[i = j])
	{
		tab[(*k)].col = ignore_white_spaces(str, qn, &i, &tabulation);
		if (*qn != 1 && (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR))
			break ;
		if (str[j = i] == '"')
		{
			*qn = *qn == 1 ? 0 : *qn + 1;
			tab[(*k)++].content = ft_strsub(str + i, 0, ++j - i);
			continue ;
		}
		while (str[j] && (*qn == 1 || (str[j] != ' ' && str[j] != '\t' &&
				str[j] != '\n')) && str[j] != '"')
			++j;
		if (j != i)
			tab[(*k)++].content = ft_strsub(str + i, 0, j - i);
	}
}

t_line		*player_spliter(char *str)
{
	static int	qn;
	t_line		*tab;
	int			k;

	if (str == 0)
		return (0);
	if ((tab = (t_line *)ft_memalloc((player_w_nb(str, qn) + 1) *
							sizeof(t_line))) == 0)
		error(MEMORY);
	k = 0;
	spliter_helper(tab, str, &qn, &k);
	return (tab);
}
