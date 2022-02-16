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

static int	check_state(t_token *tk_node)
{
	if (tk_node->state == DEFAULT)
		return (FALSE);
	else
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
			if (check_state(tmp) == TRUE)
			{
				replace_value(tmp, data);
			}
		}
		//remove_quotes();
		tmp = tmp->next;
	}
	return (SUCCESS);
}
