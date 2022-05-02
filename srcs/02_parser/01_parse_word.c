/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:24:53 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:24:54 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function fills the cmd structure with tk_str and if this cmd
 * 		  is a builtin, set the bool builtin to true.
 * 
 * @param tk_str
 */
void	fill_cmd(t_cmd *last_cmd, char *tk_str)
{
	last_cmd->infos.cmd = tk_str;
	if (!ft_strcmp("echo", tk_str)
		|| !ft_strcmp("cd", tk_str)
		|| !ft_strcmp("pwd", tk_str)
		|| !ft_strcmp("export", tk_str)
		|| !ft_strcmp("unset", tk_str)
		|| !ft_strcmp("env", tk_str)
		|| !ft_strcmp("exit", tk_str))
		last_cmd->infos.builtin = true;
}

void	parse_word(t_cmd **cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*last_cmd;

	tmp = *tk_lst;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		last_cmd = ft_lstlast_cmd(*cmd);
		if (tmp->prev == NULL || (tmp->prev && tmp->prev->type == PIPE)
			|| last_cmd->infos.cmd == NULL)
		{
			fill_cmd(last_cmd, tmp->str);
			tmp = tmp->next;
		}
		else
			fill_flags(&tmp, last_cmd);
	}
	*tk_lst = tmp;
}
