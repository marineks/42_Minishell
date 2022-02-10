#include "minishell.h"

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
// static int	exec_cmd(int *end, char **cmd, t_data *data)
// {
// 	char	*path;

// 	printf("je suis dans un nouveau child\n");
// 	close(end[1]);
// 	dup2(end[0], STDIN_FILENO);
// 	// dup2(end[1], STDOUT_FILENO);
// 	// close(end[0]);
// 	path = NULL;
// 	path = grep_path(data->envp, cmd[0]); 
// 	if (execve(path, cmd, data->envp) == -1)
// 	{
// 		perror("Execve");
// 		return (FAILURE);
// 	}
// 	close(end[0]);
// 	// close(end[1]);
// 	if (path)
// 		free(path);
// 	return (SUCCESS);
// }

static int	exec_first_cmd(t_data *data, int *end, char **cmd)
{
	char	*path;

	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	path = grep_path(data->envp, cmd[0]);
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[1]);
	if (path)
		free(path);
	return (SUCCESS);
}

static int	exec_last_cmd(t_data *data, int *end, char **cmd)
{
	char	*path;

	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	path = grep_path(data->envp, cmd[0]); 
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[0]);
	if (path)
		free(path);
	return (SUCCESS);
}

static int	exec_inter_cmd(t_data *data, int *end, char **cmd)
{
	char	*path;

	printf("je suis dans le inter\n");
	dup2(end[0], STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	path = grep_path(data->envp, cmd[0]); 
	if (execve(path, cmd, data->envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[0]);
	close(end[1]);
	if (path)
		free(path);
	printf("je suis presque sorti du inter\n");
	return (SUCCESS);
}

static int	exec_cmd(t_data *data, int i, int *end)
{
	data->pipe->cmd = ft_split(data->cmd_tab[i], ' ');
	if (!data->pipe->cmd)
		return (FAILURE);
	printf("i : %d, data->nb_cmd : %d\n", i, data->nb_cmd);
	if (i == 0)
	{	
		printf("test 1\n");
		// il faudra executer la fonction pour gerer la 1ere commande
		exec_first_cmd(data, end, data->pipe->cmd);
	}
	else if (i == data->nb_cmd - 1)
	{
		printf("test 3\n");
		// executer la fonction pour gerer la derniere commande
		exec_last_cmd(data, end, data->pipe->cmd);
	}
	else
	{
		printf("test 2\n");
		// fonction pour gerer les commandes entre la 1ere et la derniere
		exec_inter_cmd(data, end, data->pipe->cmd);
	}
	free(data->pipe->cmd);
	return (SUCCESS);
}

int	handle_pipe(int argc, char **argv, t_data *data)
{
	pid_t	pid;
	int		status;
	int		end[2];
	int		i;

	(void) argv;
	(void) argc;
	// if (!pid)
	// {
	// 	perror("Malloc pid");
	// 	return (FAILURE);
	// }
	if (pipe(end) == -1)
	{
        perror("Pipe");
        return (FAILURE);
    }
	i = 0;
	while (i < data->nb_cmd)
	{
		pid = fork();
		if (pid == - 1)
		{
			perror("Fork");
			return (FAILURE);
		}
		else if (pid == 0) // child process
		{
			// data->pipe->cmd = ft_split(data->cmd_tab[i], ' ');
			exec_cmd(data, i, end);
			// free(data->pipe->cmd);
		}
		pid++;
		i++;
		// wait(&status);
	}
	wait(&status);
	// i = 0;
	// while (i < data->nb_cmd)
	// {
	// 	waitpid(pid[i], &status, 0);
	// 	i++;
	// }
	return (SUCCESS);
}

