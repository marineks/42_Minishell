#include "exec.h"

// cmd = argv ici mais apres le parsing ce sera un tableau de cmds
static int	exec_cmd1(int *end, char **argv, char *envp[])
{
	char	**cmd;
	char	*path;

	printf("je suis dans child 1\n");
	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = "ls";
	cmd[1] = 0;
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
static int	exec_cmd2(int *end, char **cmd, char *envp[])
{
	char	*path;

	printf("je suis dans child 2\n");
	// cmd = malloc(sizeof(char *) * 3);
	// cmd[0] = "grep";
	// cmd[1] = "Makefile";
	// cmd[2] = 0;
	path = NULL;
	dup2(end[0], STDIN_FILENO);
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

// Version qui marche avec 2 pipes
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
	else if (*pid == 0) // child process 1
	{
		exec_cmd1(end, argv, envp);
		pid++;
	}
	*pid = fork();
	if (*pid == 0) // child process 2
	{
		printf("coucou\n");
		exec_cmd2(end, argv, envp);
	}
	else
	{
		wait(&status);
	}
	free(pid);
	return (SUCCESS);
}
