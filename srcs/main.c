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

// 2eme de EXCVE
// char **cmd;
// cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = "ls";
// 	cmd[1] = "-la";
// 	cmd[2] = 0;