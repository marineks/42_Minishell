/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:21:23 by msanjuan          #+#    #+#             */
/*   Updated: 2021/06/28 09:29:13 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current_node;
	t_list	*next_node;

	if (!lst || !*lst || !del)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		if (del)
			(*del)(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}
