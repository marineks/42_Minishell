#include "minishell.h"

// CREATION DE LA COPY DE ENVP - init arg_env

// ex : echo "lol | bonjour" | cat test | sleep 3
// token : echo - lol | bonjour
void	parse_word(t_data *data, t_token **tk_lst)
{
	t_token	*tmp;

	tmp = *tk_lst;
	(void)data;
	// lstaddback de struct cmd
	ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
	while (tmp->type != PIPE && tmp->type != END)
	{
		printf("je suis dans la boucle de parse_word\n");
		printf("tmp : %d, tmp de next : %d\n", tmp->type, tmp->next->type);


		// remplir infos de t infos
		tmp = tmp->next;
		// &tmp = (*tmp)->next;p
	}
	*tk_lst = tmp;
	// *tk_lst = (*tk_lst)->next;
}

void	create_cmds(t_data *data, t_token *token)
{
	t_token *tmp;

	tmp = token;
	printf("je rentre dans create cmd\n");
	while (tmp->next != NULL)
	{
		printf("tmp actuel : TYPE : %d - STR : |%s|\n", tmp->type, tmp->str);
		if (tmp->type == WORD)
			parse_word(data, &tmp);
		// else if (tmp->type == VAR)
		// 	parse_var(data, &tmp);
		else if (tmp->type == PIPE)
			break;
		// 	parse_pipe(data, &tmp);
		// else if (tmp->type == REDIR_IN)
		// 	parse_redir_in(data, &tmp);
		// else if (tmp->type == REDIR_OUT)
		// 	parse_redir_out(data, &tmp);
		// else if (tmp->type == HEREDOC)
		// 	parse_heredoc(data, &tmp);
		// else if (tmp->type == DGREATER)
		// 	parse_dgreater(data, &tmp);
	}
}
