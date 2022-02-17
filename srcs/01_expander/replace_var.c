#include "minishell.h"

int	erase_var(t_token **tk_node, char *str)
{
	int i;
	int j;
	int len;
	char *new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_len_var(str); // PB QUAND STR EST NE VAR QUIEXISTE PAS! On va lpus loin car +1 lign 20
	printf("len : %d\n", len);
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

int	replace_var(t_token **tk_node, char *var_value)
{
	if (var_value == NULL)
	{
		if (erase_var(tk_node, (*tk_node)->str) == FAILURE)
			return (FAILURE);
	}
	free(var_value);
	return (SUCCESS);
}