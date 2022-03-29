#include "minishell.h"

// CREATION DE LA COPY DE ENVP - init arg_env

void	create_cmds(t_data *data, t_token *token)
{
	t_token *tmp;

	tmp = token;
	printf("je rentre dans create cmd\n");
	while (tmp->next != NULL)
	{
		printf("tmp actuel : TYPE : %d - STR : |%s|\n", tmp->type, tmp->str);
		if (tmp->type == WORD || tmp->type == VAR)
			parse_word(data, &tmp);
		else if (tmp->type == PIPE || tmp->type == END)
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
