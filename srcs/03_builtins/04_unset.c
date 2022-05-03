/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:18:28 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 15:18:36 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	grep_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->var_name) == SUCCESS)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

/**
 * @brief  Unset values and attributes of bash variables. Unsetting a variable 
 * 		   or function that was not previously set shall not be considered an 
 * 		   error and does not cause the shell to abort.
 * 
 * 	Examples:
 * 		- Unset => does nothing
 * 		- Unset INEXISTING_VAR => does nothing
 * 		- Unset EXISTING_VAR EXISTING_VAR => unset all the vars in one go
 * 		- Unset EXISTING_VAR INEXISTING_VAR => unset the vars which exist and
 * 											   ignore the others
 * 		- Unset NUMBER => Non valid identifier and exit_code = 1
 * 
 * @param cmd The structure contaning all the infos pertaining to the command
 * 			  issued
 * @param env The address of a pointer to our chained list of envp
 * @return int - 0 for SUCCESS and 1 for FAILURE
 */
int	unset_variable(t_data *data, t_cmd *cmd)
{
	int		i;
	bool	error_occured;

	i = 0;
	error_occured = false;
	if (!cmd->infos.flags)
		return (SUCCESS);
	while (cmd->infos.flags[i])
	{
		if (is_a_valid_identifier(cmd->infos.flags[i]) == false)
			error_occured = export_err_msg(cmd->infos.flags[i]);
		else if (grep_var(data->env_export, cmd->infos.flags[i]) == SUCCESS)
		{
			ft_lst_unset_env(&data->env_export, cmd->infos.flags[i]);
			if (grep_var(data->env_copy, cmd->infos.flags[i]) == SUCCESS)
				ft_lst_unset_env(&data->env_copy, cmd->infos.flags[i]);
		}
		i++;
	}
	if (error_occured == true)
		return (FAILURE);
	g_exit_status = 0;
	return (SUCCESS);
}
