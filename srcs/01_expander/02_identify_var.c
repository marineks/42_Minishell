/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_identify_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:14:21 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:15:18 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_compliant(char c)
{
	if (c == ' ' || c == '$' || c == '\0' || c == '\'' || c == '\"'
		|| (c >= '\t' && c <= '\r')
		|| c == '=' || c == '[' || c == ']' || c == '{' || c == '}')
		return (false);
	else
		return (true);
}

int	count_len_var(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if (str[i] >= '0' && str[i] <= '9')
		return (count + 1);
	while (str[i])
	{
		if (is_var_compliant(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

char	*identify_variable(char *str)
{
	char	*var;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}	
		i++;
	}
	len = count_len_var(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	var = ft_strjoin(var, "=");
	return (var);
}
