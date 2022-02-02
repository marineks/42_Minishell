#include "exec.h"

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
static int	exec_cmd(int *end, char **cmd, t_data *data)
{
	char	*path;

	printf("je suis dans un nouveau child\n");
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	// dup2(end[1], STDOUT_FILENO);
	// close(end[0]);
	path = NULL;
	path = grep_path(data->envp, cmd[0]); 
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[0]);
	// close(end[1]);
	if (path)
		free(path);
	return (SUCCESS);
}

int	handle_pipe(int argc, char **argv, t_data *data)
{
	pid_t	*pid;
	int		status;
	int		end[2];
	int		i;

	(void) argv;
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
	while (data->nb_cmd)
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
			exec_cmd(end, data->pipe->cmd, data);
			free(data->pipe->cmd);
		}
		else
			wait(&status);
		data->nb_cmd--;
		pid++;
		i++;
	}
	return (SUCCESS);
}
