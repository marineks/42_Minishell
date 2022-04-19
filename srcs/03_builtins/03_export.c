#include "minishell.h"

bool	export_err_msg(char *line)
{

	printf("Minishell : export: « %s » : not a valid identifier\n", line);
	g_exit_status = FAILURE;
	// free(variable);
	// free(value);
	return (true);
}

// à noter : hola= est bien exporté, mais =hola donne une erreur d'identifier
bool	is_a_valid_identifier(char *line)
{
	if (line[0] >= '0' && line[0] <= '9') // si var commence par un chiffre
		return (false);
	else if (line[0] == '=') // si on a un flag qui est " =WORD"
		return (false);
	return (true);
}

static void	add_var_to_env(t_env **env_lst, char *line, char *var, char *val)
{
	t_env	*tmp;

	tmp = *env_lst;
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
		printf("Après export le dernier node: var : %s | val : %s\n", tmp->var_name, tmp->var_value);
	}
	printf("OUHHHHHHHHHHHHHHHHHHHHHHHH je viens d'addback hehehehe\n");
}
// ATTENTION ça marche : export test=1 test2=2
/*
"export test6=1 test9=2 hola" => pas de message d'erreur !!!!
"export test6=1 test9=2 =" => message d'erreur que quand la syntaxe du = est la!

 Pour cet exemple (2e IF): export test6=1 test9=2 hola test88=ok 
	/!\ Pas de msg d'err, et test88 est bien exporté
	donc ça veut dire qu'il faut passer les flags sans =
	A contrario, il n'y a qu'un msg d'err que quand il y a un = et que syntaxe
	nulle



	ATTENTION
	si la var existe deja il faut ecraser!!!!
*/
/**
 * @brief 
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	export_new_var(t_cmd *cmd, t_env **env)
{
	char	*var;
	char	*var_value;
	int		i;
	bool	error_occured;

	i = 0;
	error_occured = false;
	if (!cmd->infos.flags)
		return (SUCCESS);
	while (cmd->infos.flags[i])
	{
		var = call_me_by_your_name(cmd->infos.flags[i]);
		var_value = call_me_by_your_value(cmd->infos.flags[i]);
		printf("VAR : %s , VALUE : %s\n", var, var_value);
		if (ft_strchr(cmd->infos.flags[i], '=') == NULL)
		{
			i++;
			continue;
		}
		else if (is_a_valid_identifier(cmd->infos.flags[i]) == true)
			add_var_to_env(env, cmd->infos.flags[i], var, var_value);
		else
			error_occured = export_err_msg(cmd->infos.flags[i]);
		// free(var);
		// free(var_value);
		i++;
	}
	if (error_occured == true)
		return (FAILURE);
	return (SUCCESS);
}