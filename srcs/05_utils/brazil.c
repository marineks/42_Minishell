/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brazil.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:19:27 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:19:28 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (data->env_export)
		ft_lstclear_env(&data->env_export, &free);
	rl_clear_history ();
}
