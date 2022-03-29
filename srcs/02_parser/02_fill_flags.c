#include "minishell.h"

// ex : echo "lol | bonjour" | cat test | sleep 3
// token : echo - lol | bonjour

// si last_cmd->infos.cmd == echo et tant que tu as des vars, tu les join
char	*join_vars(t_token **tk_node)
{
	t_token	*tmp;
	char	*str;
	
	tmp = *tk_node;
	str = tmp->str;
	while (tmp->type == VAR && tmp->next->type == VAR)
	{
		str = ft_strjoin(tmp->str, tmp->next->str);
		tmp = tmp->next;
	}
	*tk_node = tmp;
	return (str);
}

int	echo_mode(t_token **tk_node, t_cmd *last_cmd)
{
	(void)tk_node;
	(void)last_cmd;
	return (SUCCESS);
}

int	default_mode(t_token **tk_node, t_cmd *last_cmd)
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
	if (!last_cmd->infos.flags)
		return (FAILURE);
	tmp = *tk_node;
	i = 0;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		last_cmd->infos.flags[i] = tmp->str;
		printf("flags :\ni : %d - str : |%s|\n", i, last_cmd->infos.flags[i]);
		i++;
		tmp = tmp->next;
	}
	*tk_node = tmp;
	return (SUCCESS);
}

int	fill_flags(t_token	**tk_node, t_cmd *last_cmd)
{
	if (!(ft_strcmp(last_cmd->infos.cmd, "echo")))
	{
		if (echo_mode(tk_node, last_cmd) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (default_mode(tk_node, last_cmd) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}