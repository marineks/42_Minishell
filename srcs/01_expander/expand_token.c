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
					if ((tmp->str[i] == '$' 
						&& is_var_compliant(tmp->str[i + 1]) == true)
						&& (tmp->state == DEFAULT || tmp->state == DOUBLE))
					{
						// printf("Valeur de i : %c et son index : %d\n", tmp->str[i], i);
						// printf("%sje suis appelé /str de i qui va dans retrieve: %s\n%s", RED, tmp->str + i, RESET);
						replace_var(&tmp, retrieve_value(tmp->str + i, data), i);
						// printf("%s Apres le replace -> tmp str : %s\n%s", PURPLE, tmp->str, RESET);
					}
					else
						i++;
				}
		}
		tmp = tmp->next;
	}
	//remove_quotes();
	return (SUCCESS);
}