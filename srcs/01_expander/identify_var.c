#include "minishell.h"


static bool	is_var_compliant(char c)
{
	// if ((c >= 'A' && c <= 'Z') 
	// 	|| (c >= '0' && c <= '9')
	// 	|| c == '_')
	if (c == ' ' || c == '$' || (c >= '\t' && c <= '\r') || c == '\'' || c == '\"')
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
	while (str[i])
	{
		if(is_var_compliant(str[i]) == false)
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
	printf("len pour compter char de la VAR : %d\n", len);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	var = ft_strjoin(var, "=");
	printf("variable identifiée: %s\n", var);
	return (var);
}
