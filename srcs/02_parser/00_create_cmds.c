/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:23:11 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:23:36 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmds(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == END)
		return ;
	while (tmp->next != NULL)
	{
		if (tmp == token)
			ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
		if (tmp->type == WORD || tmp->type == VAR)
			parse_word(&data->cmd, &tmp);
		else if (tmp->type == REDIR_IN)
			parse_redir_in(&data->cmd, &tmp);
		else if (tmp->type == REDIR_OUT)
			parse_redir_out(&data->cmd, &tmp);
		else if (tmp->type == HEREDOC)
			parse_heredoc(data, &tmp);
		else if (tmp->type == APPEND)
			parse_append(&data->cmd, &tmp);
		else if (tmp->type == PIPE)
			parse_pipe(&data->cmd, &tmp);
		else if (tmp->type == END)
			break ;
	}
}
