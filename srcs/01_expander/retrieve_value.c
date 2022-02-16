#include "minishell.h"

static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

static char	*grep_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == SUCCESS)
			break ;
		i++;
	}
	str = ft_strdup(data->envp[i] + len);
	return (str);
}

char	*retrieve_value(t_token *tk_node, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_variable(tk_node->str);
	if (var_exists(data, var) == SUCCESS)
	{
		printf("J'EXISTE\n");
		value =	grep_env_var(data, var);
		printf("ceci est value : %s\n", value);
	}
	else
	{
		value = NULL;
		printf("PROUVE QUE TU EXIIIIIIISTES\n");
	}
	free(var);
	return (value);
}