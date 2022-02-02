#include "exec.h"

int	init_struct(t_data *data, char *envp[])
{
	data->nb_cmd = 3; //(argc - 1) / 2;
	data->envp = envp;
	data->cmd_tab = (char **)malloc(sizeof(char *) * (data->nb_cmd + 1));
	if (!data->cmd_tab)
		return (FAILURE);
	data->pipe = (t_pipe *)malloc(sizeof(t_pipe) * (data->nb_cmd - 1));
	if (!data->pipe)
		return (FAILURE);
	data->pipe->cmd = NULL;
	return (SUCCESS);
}