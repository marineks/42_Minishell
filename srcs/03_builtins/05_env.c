/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:55:41 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 16:56:46 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display the env variables and values on the terminal
 * 
 * POINT CULTURE SUR LE CODE 127 :
 * Value 127 is returned by /bin/sh when the given command is not found within 
 * your PATH system variable and it is not a built-in shell command. In other 
 * words, the system understands your command, because it doesn't know where to
 * find the binary you're trying to call.
 * 
 * @param env our chained list of env variables
 */
int	get_env(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (cmd->infos.flags)
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(cmd->infos.flags[0], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		g_exit_status = 127;
		return (g_exit_status);
	}
	while (tmp)
	{
		write(cmd->infos.fd_out, tmp->var_name, ft_strlen(tmp->var_name));
		write(cmd->infos.fd_out, "=", 1);
		write(cmd->infos.fd_out, tmp->var_value, ft_strlen(tmp->var_value));
		write(cmd->infos.fd_out, "\n", 1);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
