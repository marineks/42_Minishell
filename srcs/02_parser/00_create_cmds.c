#include "minishell.h"

// CREATION DE LA COPY DE ENVP - init arg_env

// ex : echo "lol | bonjour" | cat test | sleep 3
// token : echo - lol | bonjour

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

int	fill_flags(t_token	**tk_node, t_cmd *last_cmd)
{
	int i;
	t_token	*tmp;

	i = 0;
	tmp = *tk_node;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		i++;
		tmp = tmp->next;
	}
	last_cmd->infos.flags = (char **)malloc(sizeof(char *) * (i + 1));
	tmp = *tk_node;
	i = 0;
	while (tmp->type == WORD)
	{
		// si last_cmd->infos.cmd == echo et tant que tu as des vars, tu les join
		last_cmd->infos.flags[i] = tmp->str;
		i++;
		tmp = tmp->next;
	}
	*tk_node = tmp;
}

void	parse_word(t_data *data, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*last_cmd;

	tmp = *tk_lst;
	// lstaddback de struct cmd
	ft_lstadd_back_cmd(&data->cmd, ft_lstnew_cmd(false));
	last_cmd = ft_lstlast_cmd(data->cmd);
	while (tmp->type != PIPE && tmp->type != END)
	{
		printf("je suis dans la boucle de parse_word\n");
		printf("tmp : %d, tmp de next : %d\n", tmp->type, tmp->next->type);
		// si c'est le premier c'est forcement la commande
		if (tmp == *tk_lst)
			fill_cmd(last_cmd, tmp->str);
		if (tmp->type == WORD)
			fill_flags(&tmp, last_cmd);
		// if (tmp->type == )
		// remplir infos de t infos
		printf("La cmd filled : %s\n", last_cmd->infos.cmd);
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
