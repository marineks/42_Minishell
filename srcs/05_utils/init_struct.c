/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:20:27 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 15:14:25 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*call_me_by_your_name(char *line)
{
	char	*timothee;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		i++;
	}
	timothee = ft_substr(line, 0, i);
	return (timothee);
}

char	*call_me_by_your_value(char *line)
{
	char	*var_value;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '=')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	if (start == 0)
		return (NULL);
	len = ft_strlen(line) - start;
	var_value = ft_substr(line, start, len);
	return (var_value);
}

t_env	*stock_envp_in_chained_list(char **envp)
{
	t_env	*env_list;
	char	*line;
	char	*var_name;
	char	*var_value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		line = ft_strdup(envp[i]);
		var_name = call_me_by_your_name(line);
		var_value = call_me_by_your_value(line);
		ft_lstadd_back_env(&env_list, ft_lstnew_env(line, var_name, var_value));
		i++;
	}	
	return (env_list);
}

int	init_data(t_data *data, char *envp[])
{
	data->envp = envp;
	data->env_copy = stock_envp_in_chained_list(envp);
	data->env_export = stock_envp_in_chained_list(envp);
	sort_export(data->env_export);
	data->token = NULL;
	return (SUCCESS);
}
