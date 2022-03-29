#include "minishell.h"

/**
 * @brief This functions fills the cmd structure with tk_str and if this cmd
 * 		  is a builtin, set the bool builtin to true.
 * 
 * @param tk_str 
 */
void	fill_cmd(t_cmd *last_cmd, char *tk_str)
{
	last_cmd->infos.cmd = tk_str;
	if (ft_strcmp("echo", tk_str)
		|| ft_strcmp("cd", tk_str)
		|| ft_strcmp("pwd", tk_str)
		|| ft_strcmp("export", tk_str)
		|| ft_strcmp("unset", tk_str)
		|| ft_strcmp("env", tk_str)
		|| ft_strcmp("exit", tk_str))
		last_cmd->infos.builtin = true;
}

void	parse_word(t_data *data, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*last_cmd;

	tmp = *tk_lst;
	ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
	last_cmd = ft_lstlast_cmd(data->cmd);
	while (tmp->type == WORD || tmp->type == VAR)
	{
		printf("je suis dans la boucle de parse_word\n");
		printf("tmp : %d, tmp de next : %d\n", tmp->type, tmp->next->type);
		// si c'est le premier c'est forcement la commande
		if (tmp == *tk_lst)
		{
			fill_cmd(last_cmd, tmp->str);
			printf("La cmd filled : %s\n", last_cmd->infos.cmd);
		}
		else
			fill_flags(&tmp, last_cmd);
		// &tmp = (*tmp)->next;
		tmp = tmp->next;
	}
	*tk_lst = tmp;
	// *tk_lst = (*tk_lst)->next;
}