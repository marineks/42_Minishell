#include "minishell.h"

char	*grep_value(t_env *env, char *var_name)
{
	char	*value;
	t_env	*tmp;

	value = NULL;
	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp(var_name, tmp->var_name) == SUCCESS)
		{
			value = ft_strdup(tmp->var_value);
			break;
		}
		tmp = tmp->next;
	}
	return (value);
}

/**
 * @brief Display the pwd (Print Working Directory) on the terminal
 * 
 * @param cmd the current command structure (with the info on the fd out)
 * @param env which is our linked list env_copy
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
