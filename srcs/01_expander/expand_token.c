#include "minishell.h"

/*
*	EXPANSION 101_
*	Expansion is performed on the command line after it has been split  
*	into tokens. There are seven kinds of expansion performed, but we will focus 
*	on variable expansion, as requested by the subject.
*	
*	After the expansion is performed, quote characters present in the  
*	original word are removed unless they have been quoted themselves.
*/

void	update_state(t_token **tk_node, char c)
{
	if (c == '\'' && (*tk_node)->state == DEFAULT)
		(*tk_node)->state = SIMPLE;
	else if (c == '\"' && (*tk_node)->state == DEFAULT)
		(*tk_node)->state = DOUBLE;
	else if (c == '\'' && (*tk_node)->state == SIMPLE)
		(*tk_node)->state = DEFAULT;
	else if (c == '\"' && (*tk_node)->state == DOUBLE)
		(*tk_node)->state = DEFAULT;
}

bool	var_surrounded_by_quotes(char *str, int i)
{
	printf("str[i] : %c\n", str[i]);
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false); 
	}
	return (false);
}

int	expand_tokens(t_data *data, t_token **tk_list)
{
	t_token	*tmp;
	int	i;

	tmp = *tk_list;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
				i = 0;
				while (tmp->str[i])
				{
					update_state(&tmp, tmp->str[i]);
					if (tmp->str[i] == '$'
						&& (tmp->str[i + 1] != '$' || tmp->str[i + 1] != ' ')
						&& var_surrounded_by_quotes(tmp->str, i) == false
						&& (tmp->state == DEFAULT || tmp->state == DOUBLE))
						replace_var(&tmp, retrieve_val(tmp->str + i, data), i);
					else
						i++;
				}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
