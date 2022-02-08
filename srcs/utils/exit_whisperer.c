#include "exec.h"


int	check_exit(char *line)
{
	int	i;

	i = 0;
	while ((line[i] > 8 && line[i] < 14) || line[i] == 32)
		i++;
	if (ft_strncmp((line + i), "exit", 4) == 0)
		return (SUCCESS);
	else
		return (FAILURE);
}