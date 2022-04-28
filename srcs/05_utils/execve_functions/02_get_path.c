#include "minishell.h"

static char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	if (*s1 == '\0' || *s2 == '\0')
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '/';
	i++;
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

static void	free_path_tab(char **path_tab)
{
	int	i;

	i = 0;
	while (path_tab[i])
	{
		free(path_tab[i]);
		i++;
	}
	free(path_tab);

}

// faire fonction pour récup le file de la cmd (en gros strjoin du chemin 
// + la cmd visée)
// ne pas oublier de vérifier les access du file avec fonction access
char	*grep_path(char *envp[], char *cmd)
{
	int		i;
	char	**path_tab;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 4) == SUCCESS)
			break ;
		i++;
	}
	path_tab = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_tab[i] != NULL)
	{
		path = ft_strjoin_path(path_tab[i], cmd);
		if (access(path, X_OK) == SUCCESS)
		{
			free_path_tab(path_tab);
			return (path);
		}
		free(path);
		i++;
	}
	if (path_tab)
		free_path_tab(path_tab);
	return (NULL);
}