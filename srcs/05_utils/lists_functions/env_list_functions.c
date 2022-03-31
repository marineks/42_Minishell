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
		(*del)(lst->line);
	if (del && lst && lst->var_name)
		(*del)(lst->var_name);
	if (del && lst && lst->var_value)
		(*del)(lst->var_value);
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

void	print_env(t_env *lst)
{
	t_env *tmp;
	int i = 0;
	
	printf(" ###### PRINTF DE L'ENV RECUPERE ######\n");
	tmp = lst;
	while (tmp)
	{
		// if (tmp->prev == NULL)
		printf("NODE : %d - LINE : %s - VAR_NAME : %s - VAR_VALUE: |%s|\n", i, tmp->line, tmp->var_name, tmp->var_value);
		// else
			// printf("Current str: %s ~ Previous str: %s\n", tmp->str, tmp->prev->str);
		printf("----------------------------------------------------------\n");
		tmp = tmp->next;
		i++;
	}
}
