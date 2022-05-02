/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:04:43 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:05:00 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_env(t_env *env)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**convert_env_copy_to_array(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**env_array;

	i = 0;
	tmp = env;
	env_array = (char **)malloc(sizeof(char *) * (count_len_env(env) + 1));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		env_array[i] = ft_strdup(tmp->line);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
