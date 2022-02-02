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
	i = 1;	// Pourquoi 1 et pas zero ??
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

// Test Tiff

// static int	exec_first_cmd(t_data *data, int **end, char **cmd)
// {
// 	char	*path;

// 	dup2(end[1], STDOUT_FILENO);
// 	close(end[0]);
// 	path = grep_path(data->envp, cmd[0]);
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		perror("Execve");
// 		return (FAILURE);
// 	}
// 	close(end[1]);
// 	if (path)
// 		free(path);
// 	return (SUCCESS);
// }

// static int	exec_cmd(t_data *data, int i, int **end)
// {
// 	if (i == 1) // ou 0 en fonction de ce qu'on decide avant
// 	{
// 		data->pipe->cmd = ft_split(data->cmd_tab[i], ' ');
// 		// il faudra executer la fonction pour gerer la 1ere commande
// 		exec_first_cmd(data, &end, data->pipe->cmd);
// 		free(data->pipe->cmd);
// 	}
// 	else if (i == data->nb_cmd)
// 	{
// 		// executer la fonction pour gerer la derniere commande
// 	}
// 	else
// 	{
// 		// fonction pour gerer les commandes entre la 1ere et la derniere
// 	}
// 	return (SUCCESS);
// }