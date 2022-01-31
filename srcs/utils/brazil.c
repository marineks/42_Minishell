#include "exec.h"

void	escape_to_brazil(t_data *data)
{
	if (data->cmd_tab)
		free(data->cmd_tab);
}