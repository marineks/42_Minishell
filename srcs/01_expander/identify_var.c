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
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	var = ft_strjoin(var, "=");
	printf("variable identifiée: %s\n", var);
	return (var);
}
