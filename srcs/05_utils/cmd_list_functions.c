#include "minishell.h"

t_cmd	*ft_lstnew_cmd()
{
	t_cmd	*new_block;

	new_block = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_block))
		return (NULL);
	new_block->is_pipe = false;
	// new_block->infos = NULL;
	new_block->left = NULL;
	new_block->right = NULL;
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
		while (start->right != NULL)
			start = start->right;
		start->right = new_node;
		new_node->left = start;
	}
}

void	ft_lstdelone_cmd(t_cmd *lst, void (*del)(void *))
{
	(void)(*del);
	// if (del && lst)
	// 	(*del)(lst->infos);
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
		tmp = (*lst)->right;
		ft_lstdelone_cmd(*lst, del);
		*lst = tmp;
	}
}

void	print_cmd(t_cmd *lst)
{
	t_cmd *tmp;
	int i;
	
	tmp = lst;
	i = 0;
	printf("DETAILS LIST CMDS\n");
	while (tmp)
	{
		// if (tmp->left == NULL)
		printf("is pipe : %d - LEFT : %p - RIGHT: %p\n", tmp->is_pipe, tmp->left, tmp->right);
		printf("INFOS:\nCmd : |%s|\nBuiltin : %d\nRedir_in : %dRedir_out : %d\nFd_in : %d\nFd_out : %d\n", tmp->infos.cmd, tmp->infos.builtin, tmp->infos.redir_in, tmp->infos.redir_out, tmp->infos.fd_in, tmp->infos.fd_out);
		printf("----------------------------------------------------------\n");
		tmp = tmp->right;
		i++;
	}
}
