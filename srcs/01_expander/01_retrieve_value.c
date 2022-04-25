#include "minishell.h"

static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = data->env_copy;
	// while (data->envp[i])
	// {
	// 	if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
	// 		return (SUCCESS);
	// 	i++;
	// }
	while (tmp)
	{
		if (ft_strncmp(tmp->line, var, len) == SUCCESS)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

static char	*grep_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = data->env_copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, var, len) == SUCCESS)
			break ;
		i++;
		tmp = tmp->next;
	}
	// while (data->envp[i])
	// {
	// 	if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
	// 		break ;
	// 	i++;
	// }
	// str = ft_strdup(data->envp[i] + len);
	str = ft_strdup(tmp->var_value);
	return (str);
}

char	*retrieve_val(char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_variable(str);
	if (var && var_exists(data, var) == SUCCESS)
		value =	grep_env_var(data, var);
	else
		value = NULL;
	free(var);
	return (value);
}