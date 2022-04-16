#include "minishell.h"

/**
 * @brief Display the env variables and values on the terminal
 * 
 * @param env our chained list of env variables
 */
void	get_env(t_cmd *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		write(cmd->infos.fd_out, tmp->line, ft_strlen(tmp->line));
		write(cmd->infos.fd_out, "\n", 1);
		tmp = tmp->next;
	}
}