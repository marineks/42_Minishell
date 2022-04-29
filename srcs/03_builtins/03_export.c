#include "minishell.h"

static void	add_var_to_export(t_env **env_exp, char *line, char *var, char *val)
{
	t_env	*tmp;
	char	*value;

	tmp = *env_exp;
	value = grep_value(*env_exp, var);
	if (find_str(val, "$?") == SUCCESS)
		val = replace_exit_status(val);
	if (value == NULL)
		ft_lstadd_back_env(env_exp, ft_lstnew_env(ft_strdup(line), var, val));
	else
	{
		while (tmp->next)
		{
			if (ft_strcmp(var, tmp->var_name) == SUCCESS)
				break;
			tmp = tmp->next;
		}
		free(tmp->var_value);
		tmp->var_value = val;
		free(var);
	}
	free(value);
}

static void	add_var_to_env(t_data *data, char *line, char *var, char *val)
{
	t_env	*tmp;
	char	*keep_var;
	char	*value;

	tmp = data->env_copy;
	printf("var : %s\n", var);
	keep_var = ft_strdup(var);
	add_var_to_export(&data->env_export, line, var, val);
	if (ft_strchr(line, '=') == NULL)
		return ;
	if (find_str(val, "$?") == SUCCESS)
		val = replace_exit_status(val);
	value = grep_value(data->env_copy, keep_var);
	if (value == NULL)
		ft_lstadd_back_env(&data->env_copy, ft_lstnew_env(ft_strdup(line), ft_strdup(keep_var), ft_strdup(val)));
	else
	{
		while (tmp->next)
		{
			if (ft_strcmp(keep_var, tmp->var_name) == SUCCESS)
				break;
			tmp = tmp->next;
		}
		free(tmp->var_value);
		tmp->var_value = val;
		
	}
	if (keep_var)
		free(keep_var);
	free(value);
}

static void	manage_export_alone(t_cmd *cmd, t_env **env_export)
{
	t_env	*tmp;

	tmp = *env_export;
	sort_export(tmp);
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
		// if (ft_strchr(cmd->infos.flags[i], '=') == NULL)
		// {
		// 	i++;
		// 	continue;
		// }
		if (is_a_valid_identifier(cmd->infos.flags[i]) == true)
			add_var_to_env(data, cmd->infos.flags[i],\
			call_me_by_your_name(cmd->infos.flags[i]),\
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

bool	export_err_msg(char *line)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_exit_status = 1;
	return (true);
}