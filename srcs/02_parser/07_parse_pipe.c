#include "minishell.h"

// example : echo  bonjour | wc -l
	/*
		1 cmd deja creee : pour echo bonjour
		on arrive au pipe : on doit creer une nouvelle commande
		puis creer une aure commande
	*/
void	parse_pipe(t_cmd **cmd, t_token **tk_lst)
{
	t_cmd *tmp;
	t_cmd *last_cmd;

	
	tmp = ft_lstlast_cmd(*cmd);
	// Create the pipe cmd
	ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(true));
	
	// Raccorder les nodes de la cmd précédente avec la cmd pipe
	last_cmd = ft_lstlast_cmd(*cmd);
	tmp->right = last_cmd;
	last_cmd->left = tmp;
	last_cmd->right = NULL;

	// peut etre lié aussi les fd mais pas sur car cmd->left

	// Puis créer une autre commande pour la prochaine commande 
	// (vu nos regles de syntaxe, il y aura forcement qqch apres)
	ft_lstadd_back_cmd(&last_cmd, ft_lstnew_cmd(false));
	// pour passer apres le token du pipe
	*tk_lst = (*tk_lst)->next;
	// et faire un last cmd ?
}