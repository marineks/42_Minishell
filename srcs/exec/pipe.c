#include "exec.h"

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
static int	exec_cmd1(int *end, char **argv, char *envp[])
{
	char **cmd;
	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = "ls";
	cmd[1] = 0;
	printf("je suis dans child 1\n");
	char	*path;

	path = NULL;
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	path = grep_path(envp, argv[1]); 
	if (execve(path, cmd, envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[1]);
	if (path)
		free(path);
	return (SUCCESS);
}

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
static int	exec_cmd2(int *end, char **argv, char *envp[])
{
	char **cmd;
	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = "wc";
	cmd[1] = 0;
	printf("je suis dans child 2\n");
	char	*path;

	path = NULL;
	dup2(end[1], STDIN_FILENO);
	// dup2(stdout, STDOUT_FILENO);
	close(end[1]);
	path = grep_path(envp, argv[2]); 
	if (execve(path, cmd, envp) == -1)
	{
		perror("Execve");
		return (FAILURE);
	}
	close(end[0]);
	if (path)
		free(path);
	return (SUCCESS);
}

int	handle_pipe(int argc, char **argv, char *envp[])
{
	pid_t	*pid;
	int		status;
	int		end[2];

	pid = (pid_t *)malloc(sizeof(pid_t) * argc - 1);
	if (!pid)
	{
		perror("Malloc pid");
		return (FAILURE);
	}
	// ne pas oublier de free le tab de pid;
	if (pipe(end) == -1)
	{
        perror("Pipe");
        return (FAILURE);
    }
	
	*pid = fork();
	if (*pid == - 1)
	{
		perror("Fork");
		return (FAILURE);
	}
	else if (*pid == 0) // child process
	{
		exec_cmd1(end, argv, envp);
		pid++;
	}
	else if (*pid == 0) // child process 2
	{
		printf("coucou\n");
		exec_cmd2(end, argv, envp);
	}
	else
	{
		wait(&status);
	}
	return (SUCCESS);
}

// int	handle_pipe(int argc, char **argv, char *envp[])
// {
// 	pid_t	*pid;
// 	int		status;
// 	int		nb_cmd;
// 	int		end[2];
// 	int		i;

// 	nb_cmd = argc - 1;
// 	pid = (pid_t *)malloc(sizeof(pid_t) * argc - 1);
// 	if (!pid)
// 	{
// 		perror("Malloc pid");
// 		return (FAILURE);
// 	}
// 	// ne pas oublier de free le tab de pid;
// 	if (pipe(end) == -1)
// 	{
//         perror("Pipe");
//         return (FAILURE);
//     }
// 	i = 1;
// 	while (nb_cmd)
// 	{
// 		*pid = fork();
// 		if (*pid == - 1)
// 		{
// 			perror("Fork");
// 			return (FAILURE);
// 		}
// 		else if (*pid == 0) // child process
// 		{
// 			exec_cmd(end, &argv[i], envp);
// 		}
// 		else
// 		{
// 			wait(&status);
// 			if (path)
// 				free(path);
// 		}
// 		nb_cmd--;
// 		pid++;
// 		i++;
// 	}

	


// }