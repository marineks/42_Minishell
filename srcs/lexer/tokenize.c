
#include "minishell.h"

int	is_separator(char *line, int i)
{
	if (((line[i] > 8 && line[i] < 14) || line[i] == 32))
		return (BLANK);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (DLESSER);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (DGREATER);
	else if (line[i] == '<')
		return (LESSER);
	else if (line[i] =='>')
		return (GREATER);
	else
		return (0);	
}

int	tokenize(t_data *data, char *line)
{
	(void)data;
	int	i;
	int	type;

	i = 0;
	while (line[i])
	{
		type = is_separator(line, i);
		if (type) 
		{
			// Fonction qui récupère le WORD avant le separateur
			if (type == DGREATER || type == DLESSER) // RENVOIE LE TYPE
			{
				// Fonction qui ajoute le node du séparateur et le type
				i++;
			}
			else if (type == BLANK)// separe mais ne stock le separateur
				continue;
			else
				printf("\n");
				// Fonction qui ajoute le node et le type du separateur
		}
		printf("type : %d\n", type);
		i++;
	}
	return (SUCCESS);
}