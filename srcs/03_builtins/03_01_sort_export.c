/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_01_sort_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:13:53 by tmanolis          #+#    #+#             */
/*   Updated: 2022/05/04 15:14:30 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_and_sort(t_env *current, t_env *next_node)
{
	char	*tmp_line;
	char	*tmp_var;
	char	*tmp_val;

	tmp_line = current->line;
	tmp_var = current->var_name;
	tmp_val = current->var_value;
	current->line = next_node->line;
	current->var_name = next_node->var_name;
	current->var_value = next_node->var_value;
	next_node->line = tmp_line;
	next_node->var_name = tmp_var;
	next_node->var_value = tmp_val;
}

void	sort_export(t_env *env_export)
{
	t_env	*next_node;
	t_env	*current;

	current = env_export;
	while (current != NULL)
	{
		next_node = current->next;
		while (next_node != NULL)
		{
			if (current->var_name[0] > next_node->var_name[0])
				replace_and_sort(current, next_node);
			else
				next_node = next_node->next;
		}
		current = current->next;
	}
}
