#include "exec.h"

void	escape_to_brazil(t_data *data)
{
	if (data->line)
		free(data->line);
	rl_clear_history ();
}
