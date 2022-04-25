#include "minishell.h"

int	exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->infos.cmd, "pwd") == SUCCESS)
		get_pwd(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "env") == SUCCESS)
		get_env(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "echo") == SUCCESS)
		get_echo(cmd);
	else if (ft_strcmp(cmd->infos.cmd, "export") == SUCCESS)
		export_new_var(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "cd") == SUCCESS)
		change_directory(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "unset") == SUCCESS)
		unset_variable(cmd, data->env_copy);
	else if (ft_strcmp(cmd->infos.cmd, "exit") == SUCCESS)
		exit_minishell(data, cmd);
	return (SUCCESS);
}

int	exec_one_cmd(t_data *data, t_cmd *cmd)
{
	int	pid;
	int status;
	t_exec	*exec;

	if (cmd->infos.builtin == true)
		return (exec_builtin(data, cmd));
	exec = get_execve_infos(data, cmd);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr(strerror(errno), STDERR_FILENO);
		return (FAILURE);
	}
	if (pid == 0) // child process
	{
		if (execve(exec->path, exec->cmd_and_flags, exec->env_array) == -1)
		{
			ft_putstr(strerror(errno), STDERR_FILENO);
			return (FAILURE);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	free_excve_infos(exec);
	return (SUCCESS);
}

void	redir_in_out(t_cmd *cmd, int *tube_fd)
{
	close(tube_fd[READ]);
	if (cmd->infos.fd_in > 0)
	{
		dup2(cmd->infos.fd_in, STDIN_FILENO);
		close(cmd->infos.fd_in);
	}
	if (cmd->infos.fd_out > 1)
	{
		dup2(cmd->infos.fd_out, STDOUT_FILENO);
		close(cmd->infos.fd_out);
	}
	else if (cmd->right != NULL)
		dup2(tube_fd[WRITE], STDOUT_FILENO);
	close(tube_fd[WRITE]);
}

void	child_process(t_data *data, t_cmd *cmd, int *tube_fd)
{
	t_exec	*exec;

	if (cmd->infos.error)
		g_exit_status = 1;
	// else if (is_built_in(cmd->cmd_param[0]))
	// {
	// 	close(tube_fd[0]);
	// 	if (cmd->outfile < 0 && cmd->next)
	// 		cmd->outfile = tube_fd[1];
	// 	else
	// 		close(tube_fd[1]);
	// 	launch_built_in(data, cmd);
	// }
	exec = get_execve_infos(data, cmd);
	if (exec->path)
	{
		redir_in_out(cmd, tube_fd);
		execve(exec->path, exec->cmd_and_flags, exec->env_array);
		g_exit_status = 126;
	}
	else
	{
		write(STDERR_FILENO, cmd->infos.cmd, ft_strlen(cmd->infos.cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		g_exit_status = 127;
	}
	free_excve_infos(exec);
	exit_process(data, tube_fd);
}

void	exec_cmd(t_data *data, t_cmd *cmd, int *tube_fd)
{
	data->pid = fork();
	if (data->pid < 0)
		return ;
	else if (data->pid == 0)
		child_process(data, cmd, tube_fd);
	else
		parent_process(cmd, tube_fd);
}

int	exec(t_data *data)
{
	t_cmd	*cmd_lst;
	int		tube_fd[2];

	cmd_lst = data->cmd;
	if (cmd_lst->right == NULL)
		exec_one_cmd(data, cmd_lst);
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
		wait_all_and_finish(data, data->cmd);
	}
	return (SUCCESS);
}