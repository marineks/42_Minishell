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

/**
 * @brief Insert a new chained list between the node preceding the VAR node and 
 * 		  the node after VAR, which will be deleted. In order to do so:
 * 			- First, in the case where there is a node preceding VAR
 * 
 * @param tk_lst 
 * @param new_lst 
 * @return t_token* 
 */
// t_token	*insert_lst_between(t_token **tk_lst, t_token **new_lst) // pointeur simple
// {
// 	t_token	*tmp;
// 	t_token	*end_new_list;

// 	tmp = *new_lst;
// 	if ((*tk_lst)->prev != NULL)
// 	{
// 		(*tk_lst)->prev->next = *new_lst;
// 		(*new_lst)->prev = (*tk_lst)->prev;
// 	}
// 	else
// 		*tk_lst = *new_lst;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	end_new_list = tmp;
// 	tmp->next = (*tk_lst)->next;
// 	(*tk_lst)->next->prev = end_new_list; // segfault ici
// 	free((*tk_lst)->str); //supprimer et free node de VAR initial
// 	free(*tk_lst);
// 	return (end_new_list);
// }

t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*_head;
	_head = *head;
	if (_head == NULL || _head == to_del)
		*head = insert;
	else
	{
		while (_head != to_del)
			_head = _head->next;
		insert->prev = _head->prev;
		_head->prev->next = insert;
		while (insert->next)
			insert = insert->next;
		_head->next->prev = insert;
		insert->next = _head->next;
	}
	free(to_del->str);
	free(to_del);
	return (insert);
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
