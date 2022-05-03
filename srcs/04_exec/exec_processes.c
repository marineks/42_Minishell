/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:29:28 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 15:54:50 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_process(t_data *data, int *tube_fd, t_exec *exec)
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

static void	redir_fd_and_execve(t_cmd *cmd, int *tube_fd, t_exec *exec)
{
	redir_in_out(cmd, tube_fd);
	execve(exec->path, exec->cmd_and_flags, exec->env_array);
	if (ft_strchr(cmd->infos.cmd, '/'))
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd->infos.cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	g_exit_status = 126;
}

static void	display_err_cmd_not_found(t_cmd *cmd)
{
	write(STDERR_FILENO, cmd->infos.cmd, ft_strlen(cmd->infos.cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	g_exit_status = 127;
}

void	child_process(t_data *data, t_cmd *cmd, int *tube_fd)
{
	t_exec	*exec;
	char	*path;
	char	**array_copy;

	exec = NULL;
	array_copy = convert_env_copy_to_array(data->env_copy);
	path = grep_path(array_copy, cmd->infos.cmd);
	if (cmd->infos.error)
		g_exit_status = 1;
	else if (cmd->infos.builtin == true)
	{
		redir_in_out(cmd, tube_fd);
		exec_builtin_with_pipe(data, cmd);
	}
	else if (path)
	{
		exec = get_execve_infos(data, cmd);
		redir_fd_and_execve(cmd, tube_fd, exec);
	}
	else
		display_err_cmd_not_found(cmd);
	free_double_array(array_copy);
	free(path);
	exit_process(data, tube_fd, exec);
}

void	parent_process(t_cmd *cmd, int *tube_fd)
{
	close(tube_fd[WRITE]);
	if (cmd->infos.fd_in > STDIN_FILENO)
		close(cmd->infos.fd_in);
	if (cmd->infos.fd_in == STDIN_FILENO)
		cmd->infos.fd_in = tube_fd[READ];
	if (cmd->right && cmd->right->right->infos.fd_in == STDIN_FILENO)
		cmd->right->right->infos.fd_in = tube_fd[READ];
	else
		close(tube_fd[READ]);
	return ;
}
