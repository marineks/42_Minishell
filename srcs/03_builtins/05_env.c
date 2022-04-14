#include "minishell.h"

/**
 * @brief Display the env variables and values on the terminal
 * 
 * @param env our chained list of env variables
 */
void	get_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}