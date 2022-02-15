#include "minishell.h"

static int	count_len_var(char *str)
{
	int count;

	count = 0;
	return (count);
}

/**
 * @brief Exemple : "asfdn$HOMEANs" => on doit comprendre que la variable c'est HOME
 * 			Vrai bash : si "test $HOME aSDF" => imprime "test /mnt/nfs/homes/msanjuan aSDF"
 * 			Vrai bash : si "test $HOMEaSDF" => imprime "test "
 * 			Vrai bash : si "test $HOME\nDKS" => imprime "test /mnt/nfs/homes/msanjuan\nDKS"
 * 			Vrai bash : si "test $HOME$?" => imprime "test /mnt/nfs/homes/msanjuan0"
 * 		=> DELIMITEURS: les $ et les white spaces
 * @param tk_str 
 * @param data 
 * @return char* 
 */
static char	*identify_variable(char *tk_str, t_data *data)
{
		// 1) L'idée c'est de faire: un strchr de '$' dans la str (renvoie pointeur sur début 
		//		de notre future variable)
		// 2) On split la string selon les '$' ou white spaces qu'on trouve
		// 3) Tadaa, on renvoie la variable
		//	nb : ce serait bien de stocker la tableau de str avec tout découpé,
		// comme ça on aurait plus qu'à échanger la str du $ et ensuite tout imprimer 
		// à la suite
	int		i;
	int		j;
	bool	can_copy;
	char	*var;

	i = 0;
	j = 0;
	can_copy = false;
	var = (char *)malloc(sizeof(char) * count_len_var(tk_str));
	if (!var)
		return (NULL);
	while (tk_str[i])
	{
		if (tk_str[i] == '$') // NB : ne pas oublier de ne pas copier le $ !!!!
			can_copy = true;
		if (can_copy == true)
		{
			var = copy_until_delim(tk_str, i); // PB : quand il y a deux variables dans la meme str
			break;
		}
		i++;
	}
	return (var);
}

/*
*	DESKTOP_SESSION=ubuntu => prendre ce qu'il y a après le '='
*/
static char	*grep_env_var(char *variable, t_data *data)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(variable);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], variable, len) == SUCCESS)
			break ;
		i++;
	}
	// quand on a trouvé la ligne avec la variable on la découpe et on la renvoie
	// ELSE on renvoie une ERR vu qu'on doit rien print
}

int	replace_value(t_token *tk_node, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_variable(tk_node->str, data);
	value =	grep_env_var(var, data);
	// quand on a le bout à remplacer, on reprend le tableau de str découpés dans identify_variable
	// et on remplace à la bonne ligne. On store le tout dans data (token? parsing? cmd ?)
	return (SUCCESS);
}