/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.00_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:25:48 by tmanolis          #+#    #+#             */
/*   Updated: 2022/05/03 17:39:51 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_export_alone(t_cmd *cmd, t_env **env_export)
{
	t_env	*tmp;

	sort_export(*env_export);
	tmp = *env_export;
	if (!cmd->infos.flags)
	{
		while (tmp)
		{
			ft_putstr_fd("export ", cmd->infos.fd_out);
			ft_putstr_fd(tmp->var_name, cmd->infos.fd_out);
			if (ft_strchr(tmp->line, '='))
			{
				ft_putstr_fd("=\"", cmd->infos.fd_out);
				ft_putstr_fd(tmp->var_value, cmd->infos.fd_out);
				ft_putstr_fd("\"\n", cmd->infos.fd_out);
			}
			else
				ft_putchar_fd('\n', cmd->infos.fd_out);
			tmp = tmp->next;
		}
	}
}

static void	add_var_to_export(t_env **env_exp, char *line, char *var, char *val)
{
	t_env	*tmp;

	tmp = *env_exp;
	if (find_str(val, "$?") == SUCCESS)
		val = replace_exit_status(val);
	if (is_var_already_exported(*env_exp, var) == FAILURE)
		ft_lstadd_back_env(env_exp, ft_lstnew_env(line, var, val));
	else
	{
		while (tmp->next)
		{
			if (ft_strcmp(var, tmp->var_name) == SUCCESS)
				break ;
			tmp = tmp->next;
		}
		free(tmp->line);
		if (tmp->var_value)
			free(tmp->var_value);
		tmp->line = line;
		tmp->var_value = val;
		free(var);
	}
}

static void	clean_and_replace_var(t_env *tmp, char *line, char *var, char *val)
{
	free(tmp->line);
	free(tmp->var_value);
	tmp->line = ft_strdup(line);
	tmp->var_value = val;
	free(var);
}

static void	add_var_to_env(t_data *data, char *line, char *var, char *val)
{
	t_env	*tmp;

	tmp = data->env_copy;
	add_var_to_export(&data->env_export, ft_strdup(line), ft_strdup(var), \
	ft_strdup(val));
	if (ft_strchr(line, '=') == NULL)
	{
		free(var);
		free(val);
		return ;
	}
	if (find_str(val, "$?") == SUCCESS)
		val = replace_exit_status(val);
	if (is_var_already_exported(data->env_copy, var) == FAILURE)
		ft_lstadd_back_env(&data->env_copy, ft_lstnew_env(ft_strdup(line), \
		var, val));
	else
	{
		while (tmp->next)
		{
			if (ft_strcmp(var, tmp->var_name) == SUCCESS)
				break ;
			tmp = tmp->next;
		}
		clean_and_replace_var(tmp, line, var, val);
	}
}

/**
 * @brief Set export attribute for shell variables, which shall cause them to
 * 		  be in the environment of subsequently executed commands.
 * 
 * 		  Examples:
 * 			- "Export" => does nothing
 * 			- "Export 1test", "Export 1test=foo", "Export =foo", "Export ="
 * 				=> returns an error
 * 			- "Export test=ok" => exports the variable to env
 * 			- "Export test=ok test1=bar test2=baz" => exports all the var to env
 * 			- "Export test=ok word test1=bar" => will export test and test1 and
 * 				will skip "word" without returning an error
 * 			- "Export test=ok = anothertest=ok" => will export all the correct
 * 				vars (even anothertest) and still prints the syntax error of '='
 * 
 * 		  Some "tricky" cases:
 * 			- If we export a variable that already exists, the value will be 
 * 			  replaced (export test=foo / export test=baz / => result will be
 * 			  test=baz);
 * 			- In the case "export test=hello test1=$test" in the same line, 
 * 			  the result for test1 will be "test1= "because at this time $test
 * 			  has not been exported yet. On the other side, "export test=hello"
 * 			  then "export test1=$test" on two separate commands will produce a
 * 			  "test1=hello".
 * 
 * @param cmd The structure containing all the infos pertaining to the flags
 * @param env The environment where the variables should be added
 * @return int - 0 for SUCCESS and 1 for FAILURE
 */
int	export_new_var(t_data *data, t_cmd *cmd, t_env **env_exp)
{
	int		i;
	bool	error_occured;

	i = 0;
	error_occured = false;
	manage_export_alone(cmd, env_exp);
	while (cmd->infos.flags && cmd->infos.flags[i])
	{
		if (is_a_valid_identifier(cmd->infos.flags[i]) == true)
			add_var_to_env(data, cmd->infos.flags[i], \
			call_me_by_your_name(cmd->infos.flags[i]), \
			call_me_by_your_value(cmd->infos.flags[i]));
		else
			error_occured = export_err_msg(cmd->infos.flags[i]);
		i++;
	}
	if (error_occured == true)
		return (FAILURE);
	g_exit_status = 0;
	return (SUCCESS);
}
