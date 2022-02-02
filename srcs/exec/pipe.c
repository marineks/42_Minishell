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
	int		nb_cmd;
	int		end[2]; // int **fd[i][2] => il faut 2 * nb_cnd fds et 2 * nb_cmd^2 closes de fd
	int		i;

	(void) argv;
	nb_cmd = argc - 1;
	pid = (pid_t *)malloc(sizeof(pid_t) * argc - 1);
	if (!pid)
	{
		perror("Malloc pid");
		return (FAILURE);
	}
	if (pipe(end) == -1) // PB : je pense qu'il faut piper 'nb_cmd fois'
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
			// 02/02/2022 - LES 3 LIGNES SUIVANTES S'IMPRIMENT
			// printf("je suis dedans\n");
			// for (int i = 0; data->cmd_tab[i]; i++)
			// 	printf("Nv cmd tab : %s\n", data->cmd_tab[i]);
			data->pipe->cmd = ft_split(data->cmd_tab[i], ' '); //pb avec le split
			// 02/02/2022 - QU'IMPORTE CE QUE J'ECRIS APRES, CA S'IMPRIME PAS
			// printf("coucou\n");
			// for (int i = 0; data->pipe->cmd[i]; i++)
			// 	printf("Une ligne : %s\n", data->pipe->cmd[i]);
			exec_cmd(end, data->pipe->cmd, data);
			free(data->pipe->cmd);
		}
		else
			wait(&status);
		nb_cmd--;
		pid++;
		i++;
	}
	return (SUCCESS);
}
