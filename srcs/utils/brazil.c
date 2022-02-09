#include "minishell.h"

void	free_t_pipe(t_data *data)
{
	t_list *tmp;

	if (data->pipe)
	{
		if (data->pipe->lst)
		{
			while (data->pipe->lst)
			{
				tmp = data->pipe->lst;
				data->pipe->lst = data->pipe->lst->next;
				free(tmp);
			}
			data->pipe->lst = NULL;
		}
		else
			(void) tmp;
		free(data->pipe);
	}
}

void	escape_to_brazil(t_data *data)
{
	if (data->line)
		free(data->line);
	// free_t_pipe(data);
	rl_clear_history ();
}
