#include "minishell.h"

void	escape_to_brazil(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->token)
		ft_lstclear_token(&data->token, &free);
	rl_clear_history ();
}
