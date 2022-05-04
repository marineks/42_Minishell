/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_insert_funct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:43:46 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 12:48:52 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	link_new_extremities(t_token *to_del, t_token *tmp, t_token *insert)
{
	while (tmp != to_del)
		tmp = tmp->next;
	insert->prev = tmp->prev;
	tmp->prev->next = insert;
	while (insert->next)
		insert = insert->next;
	tmp->next->prev = insert;
	insert->next = tmp->next;
}

t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = insert;
	else if (tmp == to_del)
	{
		*head = insert;
		insert->next = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = insert;
	}
	else
		link_new_extremities(to_del, tmp, insert);
	free(to_del->str);
	free(to_del);
	return (insert);
}
