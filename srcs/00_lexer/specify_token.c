/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specify_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:46:58 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 14:47:19 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if ((*tk_node)->str[i + 1] && (*tk_node)->str[i + 1] == '?')
				break ;
			if ((*tk_node)->prev && (*tk_node)->prev->type == HEREDOC)
				break ;
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
		if (check_ops_rule(&tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
