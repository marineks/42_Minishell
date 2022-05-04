/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_free_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:48:52 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 11:03:05 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	ft_lstdelone_cmd(t_cmd *lst, void (*del)(void *))
{
	(void)(*del);
	if (lst->infos.err_msg)
		free(lst->infos.err_msg);
	if (lst->infos.flags)
		free_matrix(lst->infos.flags);
	free(lst);
}

void	ft_lstclear_cmd(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->right;
		ft_lstdelone_cmd(*lst, del);
		*lst = tmp;
	}
}
