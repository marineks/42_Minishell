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

int	exec_builtin_with_pipe(t_data *data, t_cmd *cmd)
{
	int tmp_fd_out;

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
	else
	{
		write(STDERR_FILENO, cmd->infos.cmd, ft_strlen(cmd->infos.cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		g_exit_status = 127;
	}
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

void	wait_for_dat_ass(t_data *data, t_cmd *cmd)
{
	t_cmd	*tmp;
	int	status;
	int	pid;

	tmp = cmd;
	while (tmp)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = WTERMSIG(status) + 128;
			else if (WIFSTOPPED(status))
				g_exit_status = WSTOPSIG(status) + 128;
		}
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