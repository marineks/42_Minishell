#include "minishell.h"

/**
 * @brief Display the pwd (Print Working Directory) on the terminal
 * 
 * @param cmd the current command structure (with the info on the fd out)
 * @param env which is our linked list env_copy
 * @return int 0 for SUCCESS and 1 for FAILURE
 */
void	get_pwd(t_cmd *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp("PWD", tmp->var_name) == SUCCESS)
			break;
		tmp = tmp->next;
	}
	write(cmd->infos.fd_out, tmp->var_value, ft_strlen(tmp->var_value));
	write(cmd->infos.fd_out, "\n", 1);
}

// enjeu : la subtilité de la cmd prendra tout son sens quand on aura codé cd,
// pour voir si l'env et donc pwd s'actualisent bien