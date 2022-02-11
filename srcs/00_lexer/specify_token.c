#include "minishell.h"

/*
**	@brief 
**	@params
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

int	specify(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		check_var_type(&tmp);
		tmp = tmp->next;
	}
	print_token(*tk_list);
	return (SUCCESS);
}