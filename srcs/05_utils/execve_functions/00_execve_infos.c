#include "minishell.h"

t_exec	*get_execve_infos(t_data *data, t_cmd *cmd)
{
	t_exec	*exec_infos;

	exec_infos = (t_exec *)malloc(sizeof(t_exec));
	if (!exec_infos)
		return (NULL);
	exec_infos->env_array = convert_env_copy_to_array(data->env_copy);
	exec_infos->path = grep_path(exec_infos->env_array, cmd->infos.cmd);
	exec_infos->cmd_and_flags = create_cmd_array(cmd);
	return (exec_infos);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_excve_infos(t_exec *exec_infos)
{
	if (exec_infos->path)
		free(exec_infos->path);
	if (exec_infos->env_array)
		free_double_array(exec_infos->env_array);
	if (exec_infos->cmd_and_flags)
		free_double_array(exec_infos->cmd_and_flags);
	free(exec_infos);
	exec_infos = NULL;
}