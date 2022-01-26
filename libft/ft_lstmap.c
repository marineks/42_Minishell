/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:23:42 by msanjuan          #+#    #+#             */
/*   Updated: 2021/06/26 20:35:17 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy_list;
	t_list	*new;

	new = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		cpy_list = ft_lstnew((*f)(lst->content));
		if (!cpy_list)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, cpy_list);
		lst = lst->next;
	}
	return (new);
}
