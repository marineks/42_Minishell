/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:46 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 16:03:28 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_out(t_cmd *cmd, int *tube_fd)
{
	close(tube_fd[READ]);
	if (cmd->infos.builtin == false && cmd->infos.fd_in > STDIN_FILENO)
	{
		dup2(cmd->infos.fd_in, STDIN_FILENO);
		close(cmd->infos.fd_in);
	}
	if (cmd->infos.fd_out > STDOUT_FILENO)
	{
		dup2(cmd->infos.fd_out, STDOUT_FILENO);
		close(cmd->infos.fd_out);
	}
	else if (cmd->right != NULL)
		dup2(tube_fd[WRITE], STDOUT_FILENO);
	close(tube_fd[WRITE]);
}

static void	attribute_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		g_exit_status = WSTOPSIG(status) + 128;
}

void	wait_for_dat_ass(t_data *data, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		status;
	int		pid;

	tmp = cmd;
	while (tmp)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->pid)
			attribute_exit_status(status);
		if (tmp->infos.fd_out > STDOUT_FILENO)
			close(tmp->infos.fd_out);
		if (tmp->infos.fd_in > STDIN_FILENO)
			close(tmp->infos.fd_in);
		if (tmp->right)
			tmp = tmp->right->right;
		else
			tmp = tmp->right;
	}
}

void	exec_cmd(t_data *data, t_cmd *cmd, int *tube_fd)
{
	data->pid = fork();
	if (data->pid < 0)
		return ;
	else if (data->pid == 0)
	{
		interpret_signal(DEFAULT_ACTION, NULL);
		child_process(data, cmd, tube_fd);
	}
	else
		parent_process(cmd, tube_fd);
}

int	exec(t_data *data)
{
	t_cmd	*cmd_lst;
	int		tube_fd[2];

	cmd_lst = data->cmd;
	interpret_signal(IGNORE, data->cmd->infos.cmd);
	if (cmd_lst->right == NULL && cmd_lst->infos.builtin == true)
	{
		exec_one_builtin(data, cmd_lst);
		close_fd_one_builtin(cmd_lst);
	}
	else
	{
		while (cmd_lst)
		{
			if (pipe(tube_fd) == -1)
				return (-1);
			exec_cmd(data, cmd_lst, tube_fd);
			if (cmd_lst->right)
				cmd_lst = cmd_lst->right->right;
			else
				cmd_lst = cmd_lst->right;
		}
		wait_for_dat_ass(data, data->cmd);
	}
	return (SUCCESS);
}
