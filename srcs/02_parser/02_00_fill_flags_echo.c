/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_00_fill_flags_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:08:06 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 16:39:36 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function aims at bringing together all of the tokens of a single
 * 		  "quoted sentence" (i.e echo "hello    $USER") previously split.
 * 		  To do so, the tokens must fulfill the following conditions:
 * 			1) must be typed VAR 
 * 			2) the boolean "join" must be set to true (the quotes are implied)
 * 		  It is only used in the situation where the identified command is the
 * 		  the builtin "echo" and we need to print the flags without spacing them 
 * 
 * @param tk_node the address of the chained list of tokens
 * @return char* : the joined string (i.e "hello" "   " "marine" becomes
 * 					"hello    marine")
 */
char	*join_vars(t_token **tk_node)
{
	t_token	*tmp;
	char	*str;

	tmp = *tk_node;
	str = ft_strdup(tmp->str);
	while (tmp->type == VAR
		&& (tmp->next->type == VAR && tmp->next->join == true))
	{
		str = ft_strjoin(str, tmp->next->str);
		tmp = tmp->next;
	}
	*tk_node = tmp;
	return (str);
}

/**
 * @brief Counts the number of flags in the chained list of tokens.
 * 		  To count a token or multiple tokens as a flag :
 * 			- it must be either typed as a WORD or a VAR
 * 			- if it's a VAR that must be joined, we must loop through all the
 * 				tokens that fulfill these conditions before counting it as one
 * 
 * @param tmp a copy of the chained list of tokens
 * @return int : the number of flags
 */
int	count_flags(t_token *tmp)
{
	int	i;

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

/**
 * @brief The function manages the situation where the command is "echo".
 * 			- It allocates the matrix of flags w/ the count_flags function;
 * 			- Loops through tk_node while the nodes are WORD or VAR-typed
 * 				-> If the boolean "join" is set to true, we must join all the 
 * 				   tokens that are typed VAR and has the same setting of "join".
 * 				-> In the other case, we just attribute the current token's
 * 					string to the command->infos.flags[i].
 * 
 * @param tk_node the address of the chained list of tokens
 * @param last_cmd a pointer to the last command issued
 * @return int : returns 0 for SUCCESS and 1 for FAILURE
 */
int	create_flags_in_echo_mode(t_token **tk_node, t_cmd *last_cmd)
{
	int		nb_flags;
	t_token	*tmp;
	int		i;

	tmp = *tk_node;
	nb_flags = count_flags(tmp);
	last_cmd->infos.flags = (char **)malloc(sizeof(char *) * (nb_flags + 1));
	if (!last_cmd->infos.flags)
		return (FAILURE);
	i = 0;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			last_cmd->infos.flags[i] = join_vars(&tmp);
		else
			last_cmd->infos.flags[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	last_cmd->infos.flags[i] = NULL;
	*tk_node = tmp;
	return (SUCCESS);
}

static char	**copy_into_new_tab(
	int len, char **new_tab, t_cmd *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->infos.flags[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	add_flags_in_echo_mode(t_token **tk_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	int		nb_flags;
	char	**new_tab;
	t_token	*tmp;

	i = 0;
	tmp = *tk_node;
	nb_flags = count_flags(tmp);
	len = 0;
	while (last_cmd->infos.flags[len])
		len++;
	new_tab = (char **)malloc(sizeof(char *) * (nb_flags + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_into_new_tab(len, new_tab, last_cmd, tmp);
	free(last_cmd->infos.flags);
	last_cmd->infos.flags = new_tab;
	*tk_node = tmp;
	return (SUCCESS);
}
