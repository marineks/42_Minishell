#include "minishell.h"

t_cmd	*ft_lstnew_cmd()
{
	t_cmd	*new_block;

	new_block = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_block))
		return (NULL);
	new_block->cmd = NULL;
	new_block->flags = NULL;
	new_block->arg_env = NULL;
	new_block->builtin = false;
	new_block->redir_in = false;
	new_block->redir_out = false;
	new_block->fd_in = 0;
	new_block->fd_out = 0;
	new_block->error = 0;
	new_block->prev = NULL;
	new_block->next = NULL;
	return (new_block);
}


void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new_node)
{
	t_cmd	*start;

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

void	ft_lstdelone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (del && lst)
		(*del)(lst->cmd);
	// boucle special pour free les doubles tableaux
		// (*del)(lst->flags);
		// (*del)(lst->arg_env);
	// ATTENTION : peut etre close les fd ici
	free(lst);
}

void	ft_lstclear_cmd(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone_cmd(*lst, del);
		*lst = tmp;
	}
}

void	print_cmd(t_cmd *lst)
{
	t_cmd *tmp;
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
