/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:26:55 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 13:30:00 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_one_builtin(t_cmd *cmd)
{
	if (cmd->infos.fd_in > STDIN_FILENO)
		close(cmd->infos.fd_in);
	if (cmd->infos.fd_out > STDOUT_FILENO)
		close(cmd->infos.fd_out);
}

int	exec_one_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->infos.cmd, "pwd") == SUCCESS)
		get_pwd(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "env") == SUCCESS)
		get_env(cmd, &data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "echo") == SUCCESS)
		get_echo(cmd);
	else if (ft_strcmp(cmd->infos.cmd, "export") == SUCCESS)
		export_new_var(data, cmd, &data->env_export);
	else if (ft_strcmp(cmd->infos.cmd, "cd") == SUCCESS)
		change_directory(cmd, &data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "unset") == SUCCESS)
		unset_variable(data, cmd);
	else if (ft_strcmp(cmd->infos.cmd, "exit") == SUCCESS)
		exit_minishell(data, cmd);
	return (SUCCESS);
}

int	exec_builtin_with_pipe(t_data *data, t_cmd *cmd)
{
	int	tmp_fd_out;

	if (cmd->infos.fd_out > STDOUT_FILENO)
	{
		tmp_fd_out = dup(STDOUT_FILENO);
		dup2(cmd->infos.fd_out, STDOUT_FILENO);
	}
	exec_one_builtin(data, cmd);
	if (cmd->infos.fd_out > STDOUT_FILENO)
	{
		dup2(tmp_fd_out, STDOUT_FILENO);
		close(tmp_fd_out);
	}
	return (SUCCESS);
}

void	exit_process(t_data *data, int *tube_fd, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->infos.fd_in > STDIN_FILENO)
			close(cmd->infos.fd_in);
		if (cmd->infos.fd_out > STDOUT_FILENO)
			close(cmd->infos.fd_out);
		if (cmd->right)
			cmd = cmd->right->right;
		else
			cmd = cmd->right;
	}
	if (tube_fd)
	{
		close(tube_fd[READ]);
		close(tube_fd[WRITE]);
	}
	if (exec)
		free_excve_infos(exec);
	escape_to_brazil(data);
	exit(g_exit_status);
}
