#include "exec.h"


int	find_pipes(t_data *data, char *line)
{
	int	nb_pipes;
	int *pipes_pos;// stocke l'index du pipe trouvé
	int i;
	int	state;

	(void) data;
	nb_pipes = 0;
	i = 0;
	state = 0;
	pipes_pos = NULL;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|') && state == 0)
		{
			printf("Error : syntax error near unexpected token `|'\n");
			return (FAILURE);
		}
		else if (line[i] == '\'' && state == 0)
			state = 1;
		else if (line[i] == '\"' && state == 0)
			state = 2;
		else if (line[i] == '\'' && state == 1)
			state = 0;
		else if (line[i] == '\"' && state ==2)
			state = 0;
		else if (line[i] == '|' && state == 0)
		{
			nb_pipes++;
			// pipes_pos[i] = i;
		}
		i++;
	}
	printf("%d\n", nb_pipes);	
	return (nb_pipes);
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