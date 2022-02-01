#include "exec.h"

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
static int	exec_cmd(int *end, char **cmd, t_data *data)
{
	char	*path;

	// if (foo == true)
	// {
			close(end[1]);
			dup2(end[0], STDIN_FILENO);
	// }
	// else
	// {
		// dup2(end[1], STDOUT_FILENO);
		// close(end[0]);
	// }
	
	path = grep_path(data->envp, cmd[0]); 
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	// if ( foo == true)
		close(end[0]);
	// else
		// close(end[1]);
	if (path)
		free(path);
	return (SUCCESS);
}

int	handle_pipe(int argc, char **argv, t_data *data)
{
	pid_t	*pid;
	int		status;
	int		nb_cmd;
	int		end[2];
	int		i;

	nb_cmd = argc - 1;
	pid = (pid_t *)malloc(sizeof(pid_t) * argc - 1);
	if (!pid)
	{
		perror("Malloc pid");
		return (FAILURE);
	}
	if (pipe(end) == -1)
	{
        perror("Pipe");
        return (FAILURE);
    }
	i = 1;
	while (nb_cmd)
	{
		*pid = fork();
		if (*pid == - 1)
		{
			perror("Fork");
			return (FAILURE);
		}
		else if (*pid == 0) // child process
		{
			data->pipe->cmd = ft_split(data->cmd_tab[i], ' ');
			exec_cmd(end, &data->pipe->cmd, &data->envp);
			free(data->pipe->cmd);
		}
		else
			wait(&status);
		nb_cmd--;
		pid++;
		i++;
	}

}
