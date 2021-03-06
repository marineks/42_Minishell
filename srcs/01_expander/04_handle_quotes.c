/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:18:41 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:19:41 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_length(char *str, int count, int i)
{
	int	state;

	state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && state == DEFAULT)
		{
			if (str[i] == '\'')
				state = SIMPLE;
			if (str[i] == '\"')
				state = DOUBLE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && state == SIMPLE)
			|| (str[i] == '\"' && state == DOUBLE))
		{
			state = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	if_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_data *data)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = data->token;
	while (tmp)
	{
		if (if_quotes(tmp->str) == true)
			remove_quotes(&tmp);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
