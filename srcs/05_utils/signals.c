/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:26:52 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:26:53 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_basic(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_cat(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_subprocess(int signum)
{
	if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	else if (signum == SIGINT)
	{
		g_exit_status = 130;
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_ignore(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
}

static void	handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	apply_according_to_cmd(char *cmd)
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
