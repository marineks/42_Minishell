/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 09:23:59 by msanjuan          #+#    #+#             */
/*   Updated: 2022/02/08 20:13:42 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int data)
{
	t_list	*new_block;

	new_block = (t_list *)malloc(sizeof(t_list));
	if (!(new_block))
		return (NULL);
	new_block->content = data;
	new_block->next = NULL;
	return (new_block);
}
