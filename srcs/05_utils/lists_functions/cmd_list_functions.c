/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:47:02 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 10:49:03 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_infos(t_cmd **cmd)
{
	(*cmd)->infos.cmd = NULL;
	(*cmd)->infos.flags = NULL;
	(*cmd)->infos.arg_env = NULL;
	(*cmd)->infos.builtin = false;
	(*cmd)->infos.redir_in = false;
	(*cmd)->infos.redir_out = false;
	(*cmd)->infos.fd_in = 0;
	(*cmd)->infos.fd_out = 1;
	(*cmd)->infos.error = 0;
	(*cmd)->infos.err_msg = NULL;
}

t_cmd	*ft_lstnew_cmd(bool value)
{
	t_cmd	*new_block;

	new_block = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_block))
		return (NULL);
	ft_memset(new_block, 0, sizeof(t_cmd));
	new_block->is_pipe = value;
	init_infos(&new_block);
	return (new_block);
}

void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new_node)
{
	t_cmd	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->right != NULL)
			start = start->right;
		start->right = new_node;
		new_node->left = start;
	}
}

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	while (cmd->right != NULL)
		cmd = cmd->right;
	return (cmd);
}
