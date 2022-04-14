#include "minishell.h"

/**
 * @brief Display the pwd (Print Working Directory) on the terminal
 * 
 * @param env which is our linked list env_copy
 * @return int 0 for SUCCESS and 1 for FAILURE
 */
void	get_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp("PWD", tmp->var_name) == SUCCESS)
			break;
		tmp = tmp->next;
	}
	printf("%s\n", tmp->var_value);
}

// enjeu : la subtilité de la cmd prendra tout son sens quand on aura codé cd,
// pour voir si l'env et donc pwd s'actualisent bien