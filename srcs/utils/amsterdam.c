#include "minishell.h"

void	escape_to_amsterdam(t_data *data)
{
	if (data->line)
		free(data->line);
	ft_lstclear_token(&data->token, &free);
}
