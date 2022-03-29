#include "minishell.h"


static void	change_default_to_quote(t_token **tk_node, int *i)
{
	if ((*tk_node)->str[*i] == '\'')
		(*tk_node)->state = SIMPLE;
	if ((*tk_node)->str[*i] == '\"')
		(*tk_node)->state = DOUBLE;
	(*i)++;
}

static bool	if_quotes_and_default(t_token **tk_node, int i)
{
	if (((*tk_node)->str[i] == '\'' || (*tk_node)->str[i] == '\"') 
			&& (*tk_node)->state == DEFAULT)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_token **tk_node, int *i)
{
	if (((*tk_node)->str[*i] == '\'' && (*tk_node)->state == SIMPLE) 
		|| ((*tk_node)->str[*i] == '\"' && (*tk_node)->state == DOUBLE))
	{
		(*tk_node)->state = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	remove_quotes(t_token **tk_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_length((*tk_node)->str, i, i));
	if (!new_line)
		return (FAILURE);
	while ((*tk_node)->str[i])
	{
		if (if_quotes_and_default(tk_node, i) == true)
		{
			change_default_to_quote(tk_node, &i);
			continue ;
		}
		else if (change_back_to_default(tk_node, &i) == true)
			continue ;
		new_line[j++] = (*tk_node)->str[i++];
	}
	new_line[j] = '\0';
	// printf("newline : %s\n", new_line);
	free((*tk_node)->str);
	(*tk_node)->str = new_line;
	(*tk_node)->join = true;
	return (SUCCESS);
}