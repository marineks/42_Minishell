#include "minishell.h"

void create_cmds(t_data *data, t_token *token)
{
	t_token *tmp;

	tmp = token;
	printf("je rentre dans create cmd\n");
	while (tmp->next != NULL || tmp->type == END)
	{
		printf("tmp actuel : TYPE : %d - STR : |%s|\n", tmp->type, tmp->str);
		if (tmp == token) 
		{
			ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
		}	
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
		else if (tmp->type == PIPE || tmp->type == END)
			break ;
			// parse_pipe(data, &tmp);
	}
	if (data->cmd->infos.flags)
	{
		int i = 0;
		while (data->cmd->infos.flags[i])
		{
			printf("BEFORE EXIT - Print flags :\ni : %d - str : |%s|\n", i, data->cmd->infos.flags[i]);
			i++;
		}
	}
}
