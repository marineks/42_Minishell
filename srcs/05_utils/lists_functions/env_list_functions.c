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

void	ft_lst_unset_env(t_env **lst, char *var_to_del)
{
	t_env	*tmp;

	tmp = *lst;
	// trouve le bon node
	while (tmp->next)
	{
		if (ft_strcmp(var_to_del, tmp->var_name) == SUCCESS)
			break;
		tmp = tmp->next;
	}
	// raccorde (!!!! quand on supprime le 1er node)
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	else
		tmp->next->prev = NULL;
	// suppression du node
	ft_lstdelone_env(tmp, &free);

}
