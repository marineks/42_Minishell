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

int	exec_pipe(t_cmd *cmd, int pipe_fd_in)
{
	int		tube_fd[2];

	if (pipe(tube_fd) == -1)
	{
        perror("Pipe");
        return (FAILURE);
    }
	if (cmd->infos.redir_in == true)
		dup2(tube_fd[READ], cmd->infos.fd_in);
	if (cmd->infos.redir_out == true)
		dup2(tube_fd[WRITE], cmd->infos.fd_out);
	else
	{
		dup2(tube_fd[1], STDOUT_FILENO);
		close(tube_fd[0]);
	}
}

int	exec(t_data *data, t_cmd *cmd_lst, int pipe_fd_in)
{
	(void)pipe_fd_in;

	if (cmd_lst->right == NULL)
		return (exec_one_cmd(data, cmd_lst));
	else if (cmd_lst->is_pipe == true)
	{
		exec_pipe(cmd_lst, pipe_fd_in);
		// if (cmd_lst->infos.builtin == true)
		// 	exec_built_in();
		// else
		// 	exec_cmd();
	}
	return (SUCCESS);
}