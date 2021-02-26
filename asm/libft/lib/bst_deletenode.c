/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_deletenode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 00:33:49 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		bst_deletenodehelper(t_bst *root)
{
	t_bst	*tmp;

	tmp = bst_min(root->right);
	root->key = tmp->key;
	root->content = tmp->content;
	root->content_size = tmp->content_size;
	root->right = bst_deletenode(root->right, tmp->key);
}

static t_bst	*bst_freenode(t_bst *root, t_bst *direction)
{
	if (root->content)
	{
		free(root->content);
		root->content = NULL;
	}
	free(root);
	return (direction);
}

t_bst			*bst_deletenode(t_bst *root, int key)
{
	if (root == NULL)
		return (root);
	if (key < root->key)
		root->left = bst_deletenode(root->left, key);
	else if (key > root->key)
		root->right = bst_deletenode(root->right, key);
	else
	{
		if (root->left == NULL)
			return (bst_freenode(root, root->right));
		else if (root->right == NULL)
			return (bst_freenode(root, root->left));
		bst_deletenodehelper(root);
	}
	return (root);
}
