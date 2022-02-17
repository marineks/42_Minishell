#include "minishell.h"

int	erase_var(t_token **tk_node, char *str)
{
	int i;
	int j;
	int len;
	char *new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_len_var(str);
	new_str = (char *)malloc(sizeof(char) * len);
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i = i + count_len_var(str) + 1; // pour skip le $
			if (str[i] == '\0')
				break ;
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free((*tk_node)->str);
	(*tk_node)->str = new_str;
	printf("str dans le nod : %s\n", (*tk_node)->str);
	return (SUCCESS);
}

int	erase_and_replace(t_token **tk_node, char *str, char *var_value)
{
	int i;
	int j;
	int	k;
	int len;
	char *new_str;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(str) - count_len_var(str) + ft_strlen(var_value);
	printf("len : %d\n", len);
	new_str = (char *)malloc(sizeof(char) * len);
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (var_value[k])
			{
				new_str[j] = var_value[k];
				k++;
				j++;
			}
			i = i + count_len_var(str) + 1; // pour skip le $
			if (str[i] == '\0')
				break ;
			
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free((*tk_node)->str);
	(*tk_node)->str = new_str;
	printf("str dans le nod : %s\n", (*tk_node)->str);
	return (SUCCESS);
}

int	replace_var(t_token **tk_node, char *var_value)
{
	if (var_value == NULL)
	{
		if (erase_var(tk_node, (*tk_node)->str) == FAILURE)
		{
			free(var_value);
			return (FAILURE);
		}
			
	}
	else
	{
		if (erase_and_replace(tk_node, (*tk_node)->str, var_value) == FAILURE)
		{
			free(var_value);
			return (FAILURE);
		}
	}
	free(var_value);
	return (SUCCESS);
}