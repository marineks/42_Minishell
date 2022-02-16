#include "minishell.h"


static bool	is_var_compliant(char c)
{
	if ((c >= 'A' && c <= 'Z') 
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (true);
	else
		return (false);
}

static int	count_len_var(char *str)
{
	int		i;
	int		count;
	bool	can_copy; 

	count = 0;
	i = 0;
	can_copy = false;
	while (str[i])
	{
		if(is_var_compliant(str[i]) == true)
		{
			count++;
			can_copy = true;
		}
		else if (can_copy == true && is_var_compliant(str[i + 1]) == true)
		{
			break ;
		}
		i++;
	}
	printf("DI COUNT : %d\n", count);
	return (count);
}

/**
 * @brief Exemple : "asfdn$HOMEANs" => on doit comprendre que la variable c'est HOME
 * 			Vrai bash : si echo "test $HOME aSDF" => imprime "test /mnt/nfs/homes/msanjuan aSDF"
 * 			Vrai bash : si echo "test $HOMEaSDF" => imprime "test "
 * 			Vrai bash : si echo "test $HOME\nDKS" => imprime "test /mnt/nfs/homes/msanjuan\nDKS"
 * 			Vrai bash : si echo "test $HOME$?" => imprime "test /mnt/nfs/homes/msanjuan0"
 * 		=> DELIMITEURS: les $ et les white spaces
 * @param tk_str 
 * @param data 
 * @return char* 
 */
static char	*identify_variable(char *str)
{
	char	*var;
	int		start;
	int 	len;
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
	printf("variable identifiée: %s\n", var);
	return (var);
}

/*
*	DESKTOP_SESSION=ubuntu => prendre ce qu'il y a après le '='
// */
// static char	*grep_env_var(char *variable, t_data *data)
// {
// 	char	*str;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = ft_strlen(variable);
// 	while (data->envp[i])
// 	{
// 		if (ft_strncmp(data->envp[i], variable, len) == SUCCESS)
// 			break ;
// 		i++;
// 	}
// 	// quand on a trouvé la ligne avec la variable on la découpe et on la renvoie
// 	// ELSE on renvoie une ERR vu qu'on doit rien print
// }

int	replace_value(t_token *tk_node, t_data *data)
{
	// char	*value;
	char	*var;

	(void) data;
	var = identify_variable(tk_node->str);
	// value =	grep_env_var(var, data);
	
	return (SUCCESS);
}