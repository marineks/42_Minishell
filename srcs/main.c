#include "exec.h"

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	data.envp = envp;
	if (argc < 2)
		printf("Wrong input\n");
	else
		{
			if (parse_cmd(&data, argv) == FAILURE)
				return (FAILURE);
			if (handle_pipe(argc, argv, &data) == FAILURE)
			{
				perror("handle pipe");
				return (FAILURE);
			}
		}
		escape_to_brazil(&data);
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