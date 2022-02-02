#include "exec.h"

int	parse_cmd(t_data *data, char **argv)
{
	// int	i;
	// int	j;

	(void) argv;
	data->cmd_tab = (char **)malloc(sizeof(char *) * 4);
	if (!data->cmd_tab)
		return (FAILURE);
	data->cmd_tab[0] = "ls -la";
	data->cmd_tab[1] = "grep libft";
	data->cmd_tab[2] = "wc -c";
	data->cmd_tab[3] = NULL;
	// for (int i = 0; data->cmd_tab[i]; i++)
	// 			printf("Une ligne cmd tab : %s\n", data->cmd_tab[i]);
	return (SUCCESS);
}