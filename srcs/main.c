#include "exec.h"

int	main(int argc, char **argv, char *envp[])
{
	pid_t	pid;
	int		status;
	char	*path;

	if (argc != 2)
		printf("Wrong input\n");
	else
		{
			path = NULL;
			pid = fork();
			if (pid == - 1)
				return (FAILURE);
			else if (pid == 0) // là on est dans un child process
			{
				// 1) faire une fonction pour récupérer la commande (fonction de parsing qu'on va améliorer)
				// elle nous retourne le mot (cmd) qu'on va devoir rajouter à la fin du path

				// 2) fonction grep_path où on lui passe l'evnp et la cmd recupérée juste avant
				path = grep_path(envp, argv[1]);
				if (execve(path, &argv[1], envp) == -1)
				{
					printf("%sExecv Error\n%s", RED, RESET);
					return (FAILURE);
				}
			}
			wait(&status);
			if (path)
				free(path);
		}
		return (0);
}

// 2eme de EXCVE
// char **cmd;
// cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = "ls";
// 	cmd[1] = "-la";
// 	cmd[2] = 0;