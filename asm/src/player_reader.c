/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 03:53:20 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 19:06:54 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static char	player_checker(t_asm *asm_info, t_line *tab, char *quotes_num)
{
	char	type;

	type = 0;
	if (ft_strequ(tab[0].content, NAME_CMD_STRING))
		type = 0;
	else if (ft_strequ(tab[0].content, COMMENT_CMD_STRING))
		type = 1;
	else if (asm_info->champion_name != 0)
		error_row_col(NO_COMMENT, asm_info->row, tab[0].col);
	else if (asm_info->champion_comment != 0)
		error_row_col(NO_NAME, asm_info->row, tab[0].col);
	else
		error_row_col(NO_NAME_COMMENT, asm_info->row, tab[0].col);
	if (tab[1].content[0] != '"')
		error_row_col(STRING_INVALID, asm_info->row, tab[1].col);
	else
		--(*quotes_num);
	if (type == 0 && asm_info->champion_name != 0)
		error_row_col(DOUBLE_NAME, asm_info->row, tab[0].col);
	else if (type == 1 && asm_info->champion_comment != 0)
		error_row_col(DOUBLE_COMMENT, asm_info->row, tab[0].col);
	return (type);
}

static void	set_champion_infos(t_asm *asm_info, int type)
{
	if (type == 0 && asm_info->champion_name == 0)
		asm_info->champion_name = ft_strnew(0);
	if (type == 1 && asm_info->champion_comment == 0)
		asm_info->champion_comment = ft_strnew(0);
}

static void	fill_player_infos(t_asm *asm_info, t_line *tab, char *quotes_num
		, char *type)
{
	int i;

	i = (*quotes_num) == 2 ? 2 : 0;
	if ((*quotes_num) == 2)
		*type = player_checker(asm_info, tab, quotes_num);
	while (tab[i].content)
	{
		if (tab[i].content[0] == '"')
		{
			--(*quotes_num);
			set_champion_infos(asm_info, *type);
			++i;
			break ;
		}
		if (*quotes_num > 0 && *type == 0)
			asm_info->champion_name =
				ft_strjoin_free(asm_info->champion_name, tab[i].content, 1);
		else if (*quotes_num > 0 && *type == 1)
			asm_info->champion_comment =
				ft_strjoin_free(asm_info->champion_comment, tab[i].content, 1);
		++i;
	}
	if (tab[i].content != 0)
		error_row_col(STRING_INVALID, asm_info->row, tab[i].col);
}

static void	player_reader_helper(t_asm *asm_info, int fd, char *quotes_num)
{
	char	*line;
	int		status;
	t_line	*tab;
	char	type;

	type = -1;
	while ((*quotes_num) && (status = get_next_line(fd, &line)))
	{
		++(asm_info->row);
		if ((line = ft_strjoin_free(line, "\n", 1)) == 0 ||
				(tab = player_spliter(line)) == 0)
			error(MEMORY);
		if (tab[0].content == 0)
		{
			ft_memdel((void **)&line);
			free_tab_handler(tab);
			continue;
		}
		fill_player_infos(asm_info, tab, quotes_num, &type);
		free_tab_handler(tab);
		ft_memdel((void **)&line);
	}
	if (status < 0)
		error(MEMORY);
}

void		player_reader(t_asm *asm_info, int fd)
{
	char	quotes_num;

	while (asm_info->champion_name == 0 || asm_info->champion_comment == 0)
	{
		quotes_num = 2;
		player_reader_helper(asm_info, fd, &quotes_num);
		if (quotes_num != 0)
			error_row_col(STRING_INVALID, asm_info->row, -1);
		if (asm_info->champion_name != 0 && asm_info->name_length < 0)
			asm_info->name_length = ft_strlen(asm_info->champion_name);
		if (asm_info->champion_comment != 0 && asm_info->comment_length < 0)
			asm_info->comment_length = ft_strlen(asm_info->champion_comment);
		if (asm_info->name_length > PROG_NAME_LENGTH)
			error_row_col(NAME_MAX, asm_info->row, -1);
		if (asm_info->comment_length > COMMENT_LENGTH)
			error_row_col(COMMENT_MAX, asm_info->row, -1);
	}
}
