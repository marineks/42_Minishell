#include "minishell.h"

static void	handle_basic(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
}

void	interpret_signal(int action)
{
	if (action == BASIC)
	{
		signal(SIGINT, handle_basic);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
	}
	else if (action == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (action == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (action == HEREDOC)
		signal(SIGINT, handle_heredoc);
}
