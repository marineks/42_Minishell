#include "../incl/exec.h"

// faire fonction pour récup le file de la cmd (en gros strjoin du chemin + la cmd visée)
// ne pas oublier de vérifier les access du file avec fonction access
char *grep_path(char *envp[], char *cmd)
{
	int	i;
	char **path_tab;
	char *path;

	(void)cmd;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == SUCCESS)
			break;
		i++;
	}
	printf("C'est notre path <3 : %s\n", envp[i]);
	path_tab = ft_split(envp[i], ':');
	// attention on a alloué des trucs
	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], '/');
		// ne pas oublier de free path avec le 1er strjoin
		path = ft_strjoin(path, cmd);
		i++;
	}
	return (path);
}


int	main(int argc, char **argv, char *envp[])
{
	pid_t pid;
	int status;
	char *path;

	if (argc != 2)
		printf("%d\n", ERROR);
	else
		{
			
			pid = fork();
			if (pid == - 1)
				return (FAILURE);
			else if (pid == 0) // là on est dans un child process
			{
				// 1) faire une fonction pour récupérer la commande (fonction de parsing qu'on va améliorer)
				// elle nous retourne le mot (cmd) qu'on va devoir rajouter à la fin du path

				// 2) fonction grep_path où on lui passe l'evnp et la cmd recupérée juste avant
				grep_path(envp, "coucou");

				if (execve(path, argv, envp) == -1)
				{
					printf("%sExecv Error\n%s", RED, RESET);
					return (FAILURE);
				}
			}
			wait(&status);
		}
		return (0);
}


