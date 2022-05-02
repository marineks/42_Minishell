/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:26:52 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 23:11:47 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_according_to_cmd(char *cmd)
{
	if (cmd && ft_strcmp(cmd, "sleep") == SUCCESS)
	{
		signal(SIGINT, handle_subprocess);
		signal(SIGQUIT, handle_subprocess);
	}
	else if (cmd && ft_strcmp(cmd, "cat") == SUCCESS)
	{
		signal(SIGINT, handle_cat);
		signal(SIGQUIT, handle_cat);
	}
	else
	{
		signal(SIGINT, handle_ignore);
		signal(SIGQUIT, SIG_IGN);
	}	
}

void	interpret_signal(int action, char *cmd)
{
	if (action == BASIC)
	{
		signal(SIGINT, handle_basic);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
	else if (action == IGNORE)
		apply_according_to_cmd(cmd);
	else if (action == DEFAULT_ACTION)
		signal(SIGINT, SIG_DFL);
	else if (action == HEREDOC_MODE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_heredoc);
	}
}
