#include "minishell.h"

t_token	*ft_lstnew_token(char *str, int type, int state)
{
	t_token	*new_block;

	new_block = (t_token *)malloc(sizeof(t_token));
	if (!(new_block))
		return (NULL);
	new_block->str = str;
	new_block->type = type;
	new_block->state = state;
	new_block->prev = NULL;
	new_block->next = NULL;
	return (new_block);
}


void	ft_lstadd_back_token(t_token **alst, t_token *new_node)
{
	t_token	*start;

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

void	ft_lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst)
		(*del)(lst->str);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone_token(*lst, del);
		*lst = tmp;
	}
}

void	print_token(t_token *lst)
{
	t_token *tmp;
	int i = 0;
	
	printf("lst = %p\n", lst);
	tmp = lst;
	while (tmp)
	{
		// if (tmp->prev == NULL)
		printf("NODE : %d - TYPE : %d - STATE : %d - Str: |%s|\n", i, tmp->type, tmp->state, tmp->str);
		// else
			// printf("Current str: %s ~ Previous str: %s\n", tmp->str, tmp->prev->str);
		printf("----------------------------------------------------------\n");
		tmp = tmp->next;
		i++;
	}
}
