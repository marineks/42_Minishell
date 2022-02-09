
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
	else if (line[i] == '>')
		return (GREATER);
	else if (line[i] == '\0')
		return (END);
	else
		return (0);	
}

int	stock_word(t_token *tk_list, char *line, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (FAILURE);
	// printf("start : %d | index : %d\n", start, index);
	while (start < index)
	{
		word[i] = line[start];
		start++;
		i++;
	}
	word[i] = '\0';
	printf("coucou c'est notre mot : |%s|\n", word);
	// AJOUTER LE NODE
	(void)tk_list;
	return (SUCCESS);
}

int	stock_separator(t_token *tk_list, char *line, int index, int type)
{
	(void)tk_list;
	if (type == DGREATER || type == DLESSER)
		printf("separator : %c%c -> type : %d\n", line[index], line[index + 1], type);
	else
		printf("separator : %c -> type : %d\n", line[index], type);
	return (SUCCESS);
}

int	tokenize(t_data *data, char *line)
{
	(void)data;
	int	i;
	int end;
	int start;
	int	type;

	i = 0;
	start = 0;
	end = ft_strlen(line);
	while (i <= end)
	{
		type = is_separator(line, i);
		if (type) 
		{
			// printf("start : %d | i : %d\n", start, i);

			// Fonction qui récupère le WORD avant le separateur
			if (i != 0 && is_separator(line, i - 1) == 0)
				stock_word(data->token, line, i, start);
			if (type == DGREATER || type == DLESSER) // RENVOIE LE TYPE
			{
				// Fonction qui ajoute le node du séparateur et le type
				stock_separator(data->token, line, i, type);
				i++;
			}
			else if (type == BLANK) // separe mais ne stock le separateur
				printf("blank\n");
			else
			{
				// Fonction qui ajoute le node et le type du separateur
				stock_separator(data->token, line, i, type);
			}	
			start = i + 1;
		}
		// printf("type : %d\n", type);
		i++;
		
	}
	return (SUCCESS);
}