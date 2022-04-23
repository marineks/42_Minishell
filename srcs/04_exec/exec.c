#include "minishell.h"

char **create_cmd_array(t_cmd *cmd)
{
	char **new_array;
	int i;

	i = 0;
	while (cmd->infos.flags && cmd->infos.flags[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	new_array[i] = ft_strdup(cmd->infos.cmd);
	while (cmd->infos.flags && cmd->infos.flags[i])
	{
		new_array[i + 1] = ft_strdup(cmd->infos.flags[i]);
		i++;
	}
	new_array[i + 1] = NULL;
	return (new_array);
}

int	exec_one_cmd(t_data *data, t_cmd *cmd)
{
	// creer une struct pour ça et une fonction qui renvoie la struct remplie
	char	**env_array;
	char	*path;
	char	**cmd_and_flags;

	env_array = convert_env_copy_to_array(data->env_copy);
	path = NULL;
	path = grep_path(env_array, cmd->infos.cmd);
	cmd_and_flags = create_cmd_array(cmd);
	
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return (FAILURE);
	}
	if (pid == 0) // child process
	{
		if (execve(path, cmd_and_flags,env_array) == -1)
		{
			perror("Execve");
			return (FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	if (path)
		free(path);
	// creer une fonction pour free les doubles tableaux
	// free(env_array);
	// free(cmd_and_flags);
	return (SUCCESS);
}

int	exec(t_data *data, t_cmd *cmd_lst, int pipe_fd_in)
{
	(void)pipe_fd_in;

	if (cmd_lst->right == NULL)
		return (exec_one_cmd(data, cmd_lst));
	return (SUCCESS);
}