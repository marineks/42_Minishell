#include "minishell.h"

void	escape_to_amsterdam(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->token)
		ft_lstclear_token(&data->token, &free);
	if (data->cmd)
		ft_lstclear_cmd(&data->cmd, &free);
}
