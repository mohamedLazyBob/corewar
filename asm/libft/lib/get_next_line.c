/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:00:16 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	error_handler(t_bst *root, int fd, char **line)
{
	ft_strdel(line);
	bst_deletenode(root, fd);
	return (-1);
}

static int	readline(const int fd, char **line, t_bst *root, char **endl)
{
	char			buf[BUFF_SIZE + 1];
	int				read_size;

	read_size = 0;
	while ((*endl = ft_strchr(*line, '\n')) == NULL &&
			(read_size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_size] = 0;
		if ((*line = ft_strjoin_free(*line, buf, 1)) == NULL)
			return (error_handler(root, fd, line));
	}
	if (**line == 0 || read_size < 0)
	{
		if (read_size == 0)
			ft_strdel(line);
		return (read_size == 0 ? 0 : -1);
	}
	if (*endl)
		*(*endl)++ = 0;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_bst	*root;
	int				is_read;
	char			*endl;
	t_bst			*node;

	if (line == NULL || fd < 0 || (*line = ft_strnew(0)) == NULL)
		return (error_handler(root, fd, line));
	if ((node = bst_find(root, fd)) != NULL)
		if ((*line = ft_strjoin_free(*line, node->content, 1)) == NULL)
			return (error_handler(root, fd, line));
	if ((is_read = readline(fd, line, root, &endl)) <= 0)
		return (is_read == 0 ? 0 : error_handler(root, fd, line));
	if (node == NULL)
	{
		if ((node = bst_newnode(fd, NULL, 0)) == NULL)
			return (error_handler(root, fd, line));
		root = bst_insert(root, node);
	}
	if (endl || bst_modify_addr(node, NULL, 0))
		if (bst_modify_addr(node, endl, ft_strlen(endl) + 1) < 0)
			return (error_handler(root, fd, line));
	if ((*line = ft_strdup_free(line)) == NULL)
		return (error_handler(root, fd, line));
	return (1);
}
