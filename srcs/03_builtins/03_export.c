#include "minishell.h"

static void	add_var_to_env(t_env **env_lst, char *line, char *var, char *val)
{
	t_env	*tmp;

	tmp = *env_lst;
	if (find_str(val, "$?") == SUCCESS)
	{
		val = replace_exit_status(val);
	}
	if (grep_value(*env_lst, var) == NULL)
		ft_lstadd_back_env(env_lst, ft_lstnew_env(ft_strdup(line), var, val));
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
}

static void	manage_export_alone(t_cmd *cmd, t_env **env, t_env **env_export)
{
	t_env	*tmp;

	tmp = *env_export;
	if (!cmd->infos.flags)
	{
		while (tmp)
		{
			
			write(cmd->infos.fd_out, "export ", 7);
			write(cmd->infos.fd_out, tmp->var_name, ft_strlen(tmp->var_name));
			write(cmd->infos.fd_out, "=\"", 2);
			write(cmd->infos.fd_out, tmp->var_value, ft_strlen(tmp->var_value));
			write(cmd->infos.fd_out, "\"\n", 2);
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
int	export_new_var(t_cmd *cmd, t_env **env, t_env **env_export)
{
	int		i;
	bool	error_occured;

	i = 0;
	error_occured = false;
	manage_export_alone(cmd, env, env_export);
	while (cmd->infos.flags && cmd->infos.flags[i])
	{
		if (ft_strchr(cmd->infos.flags[i], '=') == NULL)
		{
			i++;
			continue;
		}
		else if (is_a_valid_identifier(cmd->infos.flags[i]) == true)
			add_var_to_env(env, cmd->infos.flags[i],\
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
