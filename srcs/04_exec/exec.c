#include "minishell.h"

int	exec_one_cmd(t_data *data, t_cmd *cmd)
{
	int	pid;
	int status;
	t_exec	*exec;

	exec = get_execve_infos(data, cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return (FAILURE);
	}
	if (pid == 0) // child process
	{
		if (execve(exec->path, exec->cmd_and_flags, exec->env_array) == -1)
		{
			perror("Execve");
			return (FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	free_excve_infos(exec);
	return (SUCCESS);
}

// 	if (cmd->infos.redir_in == true)
	// 	dup2(tube_fd[READ], cmd->infos.fd_in);
	// if (cmd->infos.redir_out == true)
	// 	dup2(tube_fd[WRITE], cmd->infos.fd_out);

int	manage_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		tube_fd[2];

	tmp = cmd;
	while (tmp->right && tmp->right->is_pipe == true)
	{
		if (pipe(tube_fd) == -1)
		{
			ft_putstr(strerror(errno), STDERR_FILENO);
			return (FAILURE);
		}
		tmp->infos.fdp_in = tube_fd[READ];
		tmp->infos.fdp_in = tube_fd[WRITE];
		tmp = tmp->right->right;
	}
	return (SUCCESS);
}

int	exec_cmd(t_data *data, t_cmd *cmd)
{
	
}

int	exec(t_data *data, t_cmd *cmd_lst, int pipe_fd_in)
{
	(void)pipe_fd_in;

	if (cmd_lst->right == NULL)
		return (exec_one_cmd(data, cmd_lst));
	else if (cmd_lst->is_pipe == true)
	{
		if (manage_pipe(cmd_lst) == FAILURE)
			return (FAILURE);
		exec_cmd(data, cmd_lst);
	}
	return (SUCCESS);
}