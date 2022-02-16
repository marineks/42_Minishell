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

static int	check_var_state(char *str)
{
	int	i;
	int state;

	i = 0;
	state = 0;
	while (str[i])
	{
		if (str[i] == '\'' && state == DEFAULT)
			state = SIMPLE;
		else if (str[i] == '\"' && state == DEFAULT)
			state = DOUBLE;
		else if (str[i] == '\'' && state == SIMPLE)
			state = DEFAULT;
		else if (str[i] == '\"' && state == DOUBLE)
			state = DEFAULT;
		else if (str[i] == '$' && state == SIMPLE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	expand_tokens(t_data *data, t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			// if (how_many_vars() > 1)
			// {
			// 	//dingueriiiiiie
			// }
			// else 
			// {
				if (check_var_state(tmp->str) == TRUE)
				{
					printf("J'EXPAND LA VAR tmp->str : %s\n", tmp->str);
					replace_var(&tmp, retrieve_value(tmp, data));
				}
			// }
		}
		tmp = tmp->next;
	}
	//remove_quotes();
	return (SUCCESS);
}
