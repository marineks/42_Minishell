#include "minishell.h"

//  if type == END
// peut etre creer un noeud de cmd vide pour pas segfault si on envoit un readline vide
// car notre tklist cree quand meme un maillon.

void create_cmds(t_data *data, t_token *token)
{
	t_token *tmp;

	tmp = token;
	// printf("je rentre dans create cmd\n");
	while (tmp->next != NULL)
	{
		// printf("tmp actuel : TYPE : %d - STR : |%s|\n", tmp->type, tmp->str);
		if (tmp == token) 
			ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
		if (tmp->type == WORD || tmp->type == VAR)
			parse_word(&data->cmd, &tmp);
		else if (tmp->type == REDIR_IN)
			parse_redir_in(&data->cmd, &tmp);
		else if (tmp->type == REDIR_OUT)
			parse_redir_out(data, &data->cmd, &tmp);
		else if (tmp->type == HEREDOC)
			parse_heredoc(data, &tmp);
		else if (tmp->type == APPEND)
			parse_append(&data->cmd, &tmp);
		else if (tmp->type == PIPE)
			parse_pipe(&data->cmd, &tmp);
		else if (tmp->type == END)
			break;
	}
	// t_cmd *cmd_tmp = data->cmd;
	// while (cmd_tmp)
	// {
	// 	// printf("BEFORE EXIT - Print cmd : %s\n", cmd_tmp->infos.cmd);
	// 	if (cmd_tmp->infos.flags)
	// 	{
	// 		int i = 0;
	// 		while (cmd_tmp->infos.flags[i])
	// 		{
	// 			// printf("BEFORE EXIT - Print flags :\ni : %d - str : |%s|\n", i, cmd_tmp->infos.flags[i]);
	// 			i++;
	// 		}
	// 	}
	// 	cmd_tmp = cmd_tmp->right;
	// }
}
