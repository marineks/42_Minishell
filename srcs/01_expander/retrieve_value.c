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

// static char	*grep_env_var(char *variable, t_data *data)
// {
// 	char	*str;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = ft_strlen(variable);
// 	while (data->envp[i])
// 	{
// 		if (ft_strncmp(data->envp[i], variable, len) == SUCCESS)
// 			break ;
// 		i++;
// 	}
// 	// quand on a trouvé la ligne avec la variable on la découpe et on la renvoie
// 	// ELSE on renvoie une ERR vu qu'on doit rien print
// }

int	replace_value(t_token *tk_node, t_data *data)
{
	// char	*value;
	char	*var;

	(void) data;
	var = identify_variable(tk_node->str);
	if (var_exists(data, var) == SUCCESS)
	{
		printf("J'EXISTE\n");
		// value =	grep_env_var(var, data);
	}
	else
	{
		printf("PROUVE QUE TU EXIIIIIIISTES\n");
	}
	// quand on aura remplacé, il faudra free var!!!
	return (SUCCESS);
}