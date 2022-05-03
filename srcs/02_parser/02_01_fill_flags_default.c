/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_01_fill_flags_default.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:41:06 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 16:44:19 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  The function fills the flags' matrix of last_cmd by default.
 * 			- It allocates the matrix of flags;
 * 			- Loops through tk_node while the nodes are WORD or VAR-typed and
 * 			  attributes the current token's string to last_cmnd->infos.flags[i]
 * 
 * @param tk_node the address of the chained list of tokens
 * @param last_cmd a pointer to the last command issued
 * @return int : returns 0 for SUCCESS and 1 for FAILURE
 */
static int	create_flags_in_default_mode(t_token **tk_node, t_cmd *last_cmd)
{
	int		i;
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
		last_cmd->infos.flags[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	last_cmd->infos.flags[i] = NULL;
	*tk_node = tmp;
	return (SUCCESS);
}

static char	**copy_default_into_new_tab(
	int len, char **new_tab, t_cmd *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->infos.flags[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static int	add_flags_in_default_mode(t_token **tk_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*tmp;

	i = 0;
	tmp = *tk_node;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		i++;
		tmp = tmp->next;
	}
	len = 0;
	while (last_cmd->infos.flags[len])
		len++;
	new_tab = (char **)malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_default_into_new_tab(len, new_tab, last_cmd, tk_node);
	free(last_cmd->infos.flags);
	last_cmd->infos.flags = new_tab;
	*tk_node = tmp;
	return (SUCCESS);
}

/**
 * @brief This function's goal is to fill the flags in the cmd->infos.flags
 * 		  structure. To do so, there are two modes :
 * 			- Either the command is the builtin "echo" and needs its own "mode"
 * 			- or else it is treated in the "default mode"
 * 
 * @param tk_node the address of the current node in the linked list of tokens
 * @param last_cmd the newest structure of command
 * @return int returns 0 for SUCCESS and 1 for FAILURE
 */
int	fill_flags(t_token	**tk_node, t_cmd *last_cmd)
{
	if (!(ft_strcmp(last_cmd->infos.cmd, "echo")))
	{
		if (!(last_cmd->infos.flags))
			return (create_flags_in_echo_mode(tk_node, last_cmd));
		else
			return (add_flags_in_echo_mode(tk_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->infos.flags))
			return (create_flags_in_default_mode(tk_node, last_cmd));
		else
			return (add_flags_in_default_mode(tk_node, last_cmd));
	}
	return (SUCCESS);
}
