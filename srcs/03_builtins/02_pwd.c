/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:53:55 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 16:54:01 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display the pwd (Print Working Directory) on the terminal
 * 
 * @param cmd the current command structure (with the info on the fd out)
 * @param env which is our linked list env_copy
 */
void	get_pwd(t_cmd *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp("PWD", tmp->var_name) == SUCCESS)
			break ;
		tmp = tmp->next;
	}
	write(cmd->infos.fd_out, tmp->var_value, ft_strlen(tmp->var_value));
	write(cmd->infos.fd_out, "\n", 1);
	g_exit_status = 0;
}
