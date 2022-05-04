/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:15:45 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 20:24:44 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *line, char *name, char *value)
{
	t_env	*new_block;

	new_block = (t_env *)malloc(sizeof(t_env));
	if (!(new_block))
		return (NULL);
	new_block->line = line;
	new_block->var_name = name;
	new_block->var_value = value;
	new_block->prev = NULL;
	new_block->next = NULL;
	return (new_block);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new_node)
{
	t_env	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	if (del && lst && lst->line)
	{
		(*del)(lst->line);
		lst->line = NULL;
	}
	if (del && lst && lst->var_name)
	{
		(*del)(lst->var_name);
		lst->var_name = NULL;
	}
	if (del && lst && lst->var_value)
	{
		(*del)(lst->var_value);
		lst->var_value = NULL;
	}
	if (lst)
		free(lst);
}

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone_env(*lst, del);
		*lst = tmp;
	}
}

/**
 * @brief Unsets the variable in env, that is : deletes the node in the chained 
 * 		  list t_env. 3 steps : 1) finds which node to delete ; 2) Links the
 * 		  node->prev with node->next ; 3) deletes the current node.
 * 
 * @param lst 
 * @param var_to_del 
 */
void	ft_lst_unset_env(t_env **lst, char *var_to_del)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp->next)
	{
		if (ft_strcmp(var_to_del, tmp->var_name) == SUCCESS)
			break ;
		tmp = tmp->next;
	}
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	else
	{
		tmp->next->prev = NULL;
		*lst = tmp->next;
	}
	ft_lstdelone_env(tmp, &free);
}
