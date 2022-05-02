/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amsterdam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:19:09 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:19:10 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
