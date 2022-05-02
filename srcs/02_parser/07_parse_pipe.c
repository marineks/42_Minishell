/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:06:56 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 16:06:57 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_cmd **cmd, t_token **tk_lst)
{
	t_cmd	*tmp;
	t_cmd	*last_cmd;

	tmp = ft_lstlast_cmd(*cmd);
	ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(true));
	last_cmd = ft_lstlast_cmd(*cmd);
	tmp->right = last_cmd;
	last_cmd->left = tmp;
	last_cmd->right = NULL;
	ft_lstadd_back_cmd(&last_cmd, ft_lstnew_cmd(false));
	*tk_lst = (*tk_lst)->next;
}
