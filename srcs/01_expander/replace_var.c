#include "minishell.h"

int	erase_var(t_token **tk_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_len_var(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + count_len_var(str + index) + 1; 
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free((*tk_node)->str);
	(*tk_node)->str = new_str;
	// printf("str dans le nod : %s\n", (*tk_node)->str);
	return (SUCCESS);
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

int	erase_and_replace(t_token **tk_node, char *str, char *var_value, int index)
{
	int i;
	int j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) *
		(ft_strlen(str) - count_len_var(str + index) + ft_strlen(var_value)));
	if (!new_str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
			i = i + count_len_var(str + index) + 1;
			if (str[i] == '\0')
				break ;	
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free((*tk_node)->str);
	(*tk_node)->str = new_str;
	// printf("str dans le nod : %s\n", (*tk_node)->str);
	return (SUCCESS);
}

int	replace_var(t_token **tk_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(tk_node, (*tk_node)->str, index) == FAILURE)
		{
			free(var_value);
			return (FAILURE);
		}
	}
	else
	{
		if (erase_and_replace(tk_node, (*tk_node)->str, var_value, index) == FAILURE)
		{
			free(var_value);
			return (FAILURE);
		}
	}
	free(var_value);
	return (SUCCESS);
}
