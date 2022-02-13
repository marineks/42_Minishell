#include "minishell.h"

/*
**	@brief  Checks whether there is a '$' in the WORD-typed token and
**		    changes the type of said token to VAR accordingly.
**	@params A pointer to a pointer on a node in chained list t_token
**
*/
void	check_var_type(t_token **tk_node)
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

/*
**	@brief  Checks whether the string is contained by simple or double quotes
**			by checking if its first character is a '\'' or a '\"' and change
**			the state of the token to SIMPLE or DOUBLE.
**	@params A pointer to a pointer on a node in chained list t_token
**
*/
void	check_state_value(t_token **tk_node)
{
	if ((*tk_node)->str[0] == '\"')
		(*tk_node)->state = DOUBLE;
	else if ((*tk_node)->str[0] == '\'')
		(*tk_node)->state = SIMPLE;
}

/*
**	@brief  After tokenising the user's command line, this function aims at
**			further specifying the tokens before eventually expanding them.
**	@params A pointer to a pointer to the chained list t_token
**
*/
int	specify(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		check_var_type(&tmp);
		check_state_value(&tmp);
		tmp = tmp->next;
	}
	print_token(*tk_list);
	return (SUCCESS);
}