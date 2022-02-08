#include "exec.h"

int	separate_cmd_lines(t_data *data)
{
	find_pipes(data, data->line);
	// split_pipe(data, data->line);
	return (SUCCESS);
}