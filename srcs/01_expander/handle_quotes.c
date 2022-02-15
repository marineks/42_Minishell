#include "minishell.h"

// int	removes_quotes(t_token **tk_node)
// {
// 	char	*new_line;
// 	int		length;
// 	int		prev_index;
// 	int		index;
// 	int		i;

// 	i = 0;
// 	prev_index = 0;
// 	index = 0;
// 	// Parcourir la string jusqu'à rencontrer une quote et change le state
// 	while ((*tk_node)->str[i])
// 	{
// 		if ((*tk_node)->str[i] == '\'' || (*tk_node)->str[i] == '\"')
// 		{
// 			if ((*tk_node)->str[i] == '\'')
// 				(*tk_node)->state = SIMPLE;
// 			if ((*tk_node)->str[i] == '\"')
// 				(*tk_node)->state = DOUBLE;
// 			prev_index = i;
// 			break;
// 		}
// 		i++;
// 	}
	
// 	// On copie de prev_index à i le 1er bout de str dans char *newline. ex: glou
// 	// Puis on check le state du bout de str restant, jusqu'à ce qu'on croise le même state ex: 'piou |"'
// 	// Quand c'est le cas on fait un strdup => Marine : plus un strjoin non?

// }

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

	i = 0;
	new_line = (char *)malloc(sizeof(char) * count_length((*tk_node)->str, i, i));
	while ((*tk_node)->str[i]) // Parcourir la string jusqu'à rencontrer une quote et change le state
	{
		if ((*tk_node)->str[i] == '\'' || (*tk_node)->str[i] == '\"')
		{
			if ((*tk_node)->str[i] == '\'')
				(*tk_node)->state = SIMPLE;
			if ((*tk_node)->str[i] == '\"')
				(*tk_node)->state = DOUBLE;
			// prev_index = i;
			break;
		}
		i++;
	}
	// On copie de prev_index à i le 1er bout de str dans char *newline. ex: glou
	// Puis on check le state du bout de str restant, jusqu'à ce qu'on croise le même state ex: 'piou |"'
	// Quand c'est le cas on fait un strdup => Marine : plus un strjoin non?

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
			printf("Résultat de count len: %d\n", count_length(tmp->str, i, i));
			// removes_quotes(&tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);

}