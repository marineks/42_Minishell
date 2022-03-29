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
	while (tmp->type == VAR && (tmp->next->type == VAR && tmp->next->join == true))
	{
		str = ft_strjoin(tmp->str, tmp->next->str);
		tmp = tmp->next;
	}
	*tk_node = tmp;
	return (str);
}

int	count_flags(t_token *tmp)
{
	int i;

	i = 0;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->type == VAR && tmp->join == true)
		{
			while (tmp->type == VAR && tmp->join == true)
				tmp = tmp->next;
			i++;
		}
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}

int	echo_mode(t_token **tk_node, t_cmd *last_cmd)
{
	int nb_flags;
	t_token	*tmp;
	int i;

	tmp = *tk_node;
	nb_flags = count_flags(tmp);
	printf("nb_flags dans echo mode : %d\n", nb_flags);
	last_cmd->infos.flags = (char **)malloc(sizeof(char *) * (nb_flags + 1));
	if (!last_cmd->infos.flags)
		return (FAILURE);
	i = 0;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
		{
			last_cmd->infos.flags[i] = tmp->str;
			printf("je suis passé dans le join == true\n");
		}
		else
			last_cmd->infos.flags[i] = tmp->str;
		printf("flags :\ni : %d - str : |%s|\n", i, last_cmd->infos.flags[i]);
		i++;
		tmp = tmp->next;
	}
	last_cmd->infos.flags[i] = NULL;
	*tk_node = tmp;
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
	last_cmd->infos.flags[i] = NULL;
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