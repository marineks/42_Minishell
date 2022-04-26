#include "minishell.h"

int	count_len_env(t_env *env)
{
	int len;
	t_env *tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**convert_env_copy_to_array(t_env *env)
{
	int i;
	t_env *tmp;
	char **env_array;

	i = 0;
	tmp = env;
	env_array = (char **)malloc(sizeof(char *) * (count_len_env(env) + 1));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		env_array[i] = ft_strdup(tmp->line);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;

	// tmp = env;
	// i = 0;
	// while (tmp)
	// {
	// 	printf("ENV ARRAY - i : %d - line : %s\n", i, env_array[i]);
	// 	tmp = tmp->next;
	// 	i++;
	// }
	return (env_array);
}