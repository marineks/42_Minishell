#include "exec.h"

void	escape_to_brazil(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_tab)
	{
		// while (data->cmd_tab[i])
		// {
		// 	printf("tada %s\n", data->cmd_tab[i]);
		// 	free(data->cmd_tab[i]);
		// 	i++;
		// }
		free(data->cmd_tab);
	}
	if (data->pipe)
		free(data->pipe);
}