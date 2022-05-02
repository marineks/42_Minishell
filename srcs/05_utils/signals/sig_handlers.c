/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:11:39 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 23:13:46 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_basic(int signum)
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

void	handle_cat(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_subprocess(int signum)
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

void	handle_ignore(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
}

void	handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}
