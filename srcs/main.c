#include "exec.h"

int	main(int argc, char **argv, char *envp[])
{

	if (argc != 3)
		printf("Wrong input\n");
	else
		{
			if (handle_pipe(argc, argv, envp) == FAILURE)
			{
				perror("handle pipe");
				return (FAILURE);
			}
		}
		return (0);
}

// int	main(int argc, char **argv, char *envp[])
// {
// 	char *path;

// 	if (argc < 1)
// 		return (FAILURE);
// 	path = grep_path(envp, argv[1]); 
// 	if (execve(path, &argv[1], envp) == -1)
// 	{
// 		perror("Execve");
// 		return (FAILURE);
// 	}
// }

// 2eme de EXCVE
// char **cmd;
// cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = "ls";
// 	cmd[1] = "-la";
// 	cmd[2] = 0;