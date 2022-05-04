/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_02_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:34:08 by tmanolis          #+#    #+#             */
/*   Updated: 2022/05/04 15:18:52 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the variable given is a valid variable according to 
 * 		  POSIX standards.
 * 
 * 			Examples where the line is not a valid identifier:
 * 			- The variable begins by a digit (export 1test=foo);
 * 			- The variable begins by the char '=' (export =foo).
 * 
 * @param line The variable to check
 */
bool	is_a_valid_identifier(char *line)
{
	if (line[0] >= '0' && line[0] <= '9')
		return (false);
	else if (line[0] == '=')
		return (false);
	return (true);
}

int	is_var_already_exported(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, var_name) == SUCCESS)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

bool	export_err_msg(char *line)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_exit_status = 1;
	return (true);
}

void	free_var_and_val(char *var, char *val)
{
	free(var);
	free(val);
}
