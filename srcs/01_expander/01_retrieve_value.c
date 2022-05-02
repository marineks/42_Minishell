/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_retrieve_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:09:16 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:13:57 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = data->env_copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, var, len) == SUCCESS)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

static char	*grep_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = data->env_copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->line, var, len) == SUCCESS)
			break ;
		i++;
		tmp = tmp->next;
	}
	str = ft_strdup(tmp->var_value);
	return (str);
}

char	*retrieve_val(char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_variable(str);
	if (var && var_exists(data, var) == SUCCESS)
		value = grep_env_var(data, var);
	else
		value = NULL;
	free(var);
	return (value);
}
