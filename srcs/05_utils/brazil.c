#include "minishell.h"

void	escape_to_brazil(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->token)
		ft_lstclear_token(&data->token, &free);
	if (data->cmd)
		ft_lstclear_cmd(&data->cmd, &free);
	if (data->env_copy)
		ft_lstclear_env(&data->env_copy, &free);
	rl_clear_history ();
	// clear_history ();
}
