#include "minishell.h"

/*
** Moyen de récupérer la readline
*/
int	init_data(t_data *data, char *envp[])
{
	// data->nb_cmd = 3; //(argc - 1) / 2;
	data->envp = envp;
	data->pipe = (t_pipe *)malloc(sizeof(t_pipe) * 1);
	if (!data->pipe)
		return (FAILURE);
	data->pipe->lst = NULL;
	data->pipe->nb_pipes = 0;
	// data->cmd_tab = (char **)malloc(sizeof(char *) * (data->nb_cmd + 1));
	// if (!data->cmd_tab)
	// 	return (FAILURE);
	return (SUCCESS);
}