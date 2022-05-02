/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_create_cmd_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:09:01 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:09:09 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_cmd_array(t_cmd *cmd)
{
	char	**new_array;
	int		i;

	i = 0;
	while (cmd->infos.flags && cmd->infos.flags[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	new_array[i] = ft_strdup(cmd->infos.cmd);
	while (cmd->infos.flags && cmd->infos.flags[i])
	{
		new_array[i + 1] = ft_strdup(cmd->infos.flags[i]);
		i++;
	}
	new_array[i + 1] = NULL;
	return (new_array);
}
