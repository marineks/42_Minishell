#include "minishell.h"

void	init_infos(t_cmd **cmd)
{
	(*cmd)->infos.cmd = NULL;
	(*cmd)->infos.flags = NULL;
	(*cmd)->infos.arg_env = NULL;
	(*cmd)->infos.builtin = false;
	(*cmd)->infos.redir_in = false;
	(*cmd)->infos.redir_out = false;
	(*cmd)->infos.fd_in = 0;
	(*cmd)->infos.fd_out = 1;
	(*cmd)->infos.error = 0;
	(*cmd)->infos.err_msg  = NULL;
}

t_cmd	*ft_lstnew_cmd(bool value)
{
	t_cmd	*new_block;

	new_block = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_block))
		return (NULL);
	ft_memset(new_block, 0, sizeof(t_cmd));
	new_block->is_pipe = value;
	init_infos(&new_block);
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

void	free_matrix(char **tab)
{
	int i;

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
	// if (del && lst)
	// 	(*del)(lst->infos);
	// boucle speciale pour free les doubles tableaux
	if (lst->infos.err_msg)
		free(lst->infos.err_msg);
	if (lst->infos.flags)
		free_matrix(lst->infos.flags);
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

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	while (cmd->right != NULL)
		cmd = cmd->right;
	return (cmd);
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
