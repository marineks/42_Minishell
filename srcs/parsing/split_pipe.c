#include "minishell.h"

/*
**	This function :
**	- finds the correct count of pipes in the user's line
**	- stores the index of each "correct" pipe in a linked list
**	- returns an error when several pipes follow one another without a 
**	  WORD-typed token in-between.
*/
int	find_pipes(t_data *data, char *line)
{
	int i;
	int	state;

	i = 0;
	state = 0;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|') && state == 0)
		{
			printf("Error : syntax error near unexpected token '|'\n");
			return (FAILURE);
		}
		else if (line[i] == '\'' && state == DEFAULT)
			state = SIMPLE;
		else if (line[i] == '\"' && state == DEFAULT)
			state = DOUBLE;
		else if (line[i] == '\'' && state == SIMPLE)
			state = DEFAULT;
		else if (line[i] == '\"' && state == DOUBLE)
			state = DEFAULT;
		else if (line[i] == '|' && state == DEFAULT)
		{
			data->pipe->nb_pipes++;
			ft_lstadd_back(&data->pipe->lst, ft_lstnew(i));
			printf("position du pipe: %d\n", i);
		}
		i++;
	}
	printf("%d\n", data->pipe->nb_pipes);
	if (data->pipe->nb_pipes > 0)
	{
		while (data->pipe->lst)
		{
			printf("position du pipe dans lst : %d\n", data->pipe->lst->content);
			data->pipe->lst = data->pipe->lst->next;
		}
	}
	return (SUCCESS);
}


// char **split_pipe(t_data *data, char *line)
// {
// 	int i;
// 	int	nb_pipe;

// 	data->nb_cmd = find_pipes(data, line);
// 	i = 0;
// 	while (line[i])
// 	{

// 	}
// }