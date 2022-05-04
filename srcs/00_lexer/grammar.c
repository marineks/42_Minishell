/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:45:13 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 17:51:25 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether there are two consecutive operators or more in the 
 * 		  chained list of tokens.
 * 		  Small exception : the case where the operators are PIPE and REDIR_OUT
 *		  i.e "echo coucou |>test1.txt"
		  Nb: Why >= 4 ? Because the operators' enums begin from PIPE (4).
 * @param tk_node: A pointer to a node of the linked list of tokens.
 * 
 */
static int	check_consecutive_ops(t_token *tk_node)
{
	if (tk_node->next)
	{
		if (tk_node->type >= 4 && tk_node->next->type == END)
			return (TRUE);
		if (tk_node->type > 4 && tk_node->next
			&& (tk_node->next->type != WORD && tk_node->next->type != VAR))
			return (TRUE);
		if (tk_node->type >= 4 && tk_node->next->type == PIPE)
			return (TRUE);
		if ((tk_node->type >= 4 && tk_node->next->type == PIPE)
			&& tk_node->next->type != END)
			return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief 
 * 
 * @param tk_list 
 *
 */
int	check_ops_rule(t_token **tk_list)
{
	t_token	*tmp;

	tmp = *tk_list;
	while (tmp)
	{
		if (check_consecutive_ops(tmp) == TRUE)
		{
			printf("Syntax error near unexpected token `%s'\n", tmp->str);
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
