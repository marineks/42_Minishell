#include "minishell.h"

/**
 * @brief 
 * 
 * @param tk_node 
 * @return int 
 */
static int	check_consecutive_ops(t_token *tk_node)
{
	if (tk_node->next)
	{
		if (tk_node->type == PIPE && tk_node->next->type == GREATER)	// cas "echo coucou |>test1.txt"
			return (FALSE);
		else if ((tk_node->type >= 4 && tk_node->next->type >= 4) 
			&& tk_node->next->type != END)
			return (TRUE);
	}
	return (FALSE);
}

int	apply_grammar(t_token **tk_list)
{
	t_token *tmp;

	tmp = *tk_list;
	while (tmp)
	{
		if (check_consecutive_ops(tmp) == TRUE)
		{
			printf("Syntax error near unexpected token `%s'\n", tmp->str);
			return (FALSE);
		}
		tmp = tmp->next;
	}
	print_token(*tk_list);
	return (SUCCESS);
}