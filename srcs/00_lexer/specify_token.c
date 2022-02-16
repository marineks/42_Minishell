#include "minishell.h"

/**
*	@brief  Checks whether there is a '$' in the WORD-typed token and
*		    changes the type of said token to VAR accordingly.
*	@param  tk_node: A pointer to a pointer on a node in chained list t_token
*
*/
static void	check_var_type(t_token **tk_node)
{
	int	i;

	i = 0;
	while ((*tk_node)->str[i])
	{
		if ((*tk_node)->str[i] == '$')
		{
			(*tk_node)->type = VAR;
			return ;
		}
		i++;
	}
}

/**
*	@brief  After tokenising the user's command line, this function aims at
*			further specifying the tokens before eventually expanding them.
*	@param  tk_list: A pointer to a pointer to the chained list t_token
*
*/
int	specify(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		check_var_type(&tmp);
		if (check_ops_rule(&tmp) == FAILURE) // Les règles de grammaire doivent s'appliquer cmd par cmd
			return (FAILURE);
		tmp = tmp->next;
	}
	print_token(*tk_list);
	return (SUCCESS);
}
