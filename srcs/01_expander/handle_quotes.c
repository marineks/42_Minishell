#include "minishell.h"


int	count_length(char *str, int count, int i)
{
	int	state;

	state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && state == DEFAULT)
		{
			if (str[i] == '\'')
				state = SIMPLE;
			if (str[i] == '\"')
				state = DOUBLE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && state == SIMPLE) 
			|| (str[i] == '\"' && state == DOUBLE))
		{
			state = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

int	removes_quotes(t_token **tk_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * count_length((*tk_node)->str, i, i));
	if (!new_line)
		return (FAILURE);
	while ((*tk_node)->str[i])
	{
		if (((*tk_node)->str[i] == '\'' || (*tk_node)->str[i] == '\"') && (*tk_node)->state == DEFAULT)
		{
			if ((*tk_node)->str[i] == '\'')
				(*tk_node)->state = SIMPLE;
			if ((*tk_node)->str[i] == '\"')
				(*tk_node)->state = DOUBLE;
			i++;
			continue ;
		}
		else if (((*tk_node)->str[i] == '\'' && (*tk_node)->state == SIMPLE) 
			|| ((*tk_node)->str[i] == '\"' && (*tk_node)->state == DOUBLE))
		{
			(*tk_node)->state = DEFAULT;
			i++;
			continue ;
		}
		new_line[j] = (*tk_node)->str[i];
		j++;
		i++;
	}
	new_line[j] = '\0';
	printf("newline : %s\n", new_line);
	free((*tk_node)->str);
	(*tk_node)->str = new_line;
	return (SUCCESS);
}

bool	if_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_data *data)
{
	t_token *tmp;
	int i;

	i = 0;
	tmp = data->token;
	while (tmp)
	{
		if (if_quotes(tmp->str) == true) // si quotes dans la string
		{
			removes_quotes(&tmp);
			printf("tmp str: %s\n", tmp->str);
		}
			
			// printf("Résultat de count len: %d\n", count_length(tmp->str, i, i));
			// removes_quotes(&tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);

}