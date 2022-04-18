#include "minishell.h"

/**
 * @brief Display the env variables and values on the terminal
 * 
 * @param env our chained list of env variables
 */
int	get_env(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	g_exit_status = 0;
	if (cmd->infos.flags)
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(cmd->infos.flags[0], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		g_exit_status = 127;
		return (g_exit_status);
	}
	while (tmp->next)
	{
		write(cmd->infos.fd_out, tmp->line, ft_strlen(tmp->line));
		write(cmd->infos.fd_out, "\n", 1);
		tmp = tmp->next;
	}
	return (g_exit_status);
}

/* POINT CULTURE SUR LE CODE 127 :
Value 127 is returned by /bin/sh when the given command is not found within your
PATH system variable and it is not a built-in shell command. In other words, the
system understands your command, because it doesn't know where to find 
the binary you're trying to call.
*/