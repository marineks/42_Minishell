#include "exec.h"

int	parse_cmd(t_data *data, char **argv)
{
	(void) argv;
	
	// data->cmd_tab[0] = (char *)malloc(sizeof(char) * ft_strlen("ls -la") + 1);
	data->cmd_tab[0] = "ls -la";
	// data->cmd_tab[1] = (char *)malloc(sizeof(char) * ft_strlen("grep libft") + 1);
	data->cmd_tab[1] = "grep libft";
	// data->cmd_tab[2] = (char *)malloc(sizeof(char) * ft_strlen("wc -c") + 1);
	data->cmd_tab[2] = "wc -c";
	// data->cmd_tab[3] = (char *)malloc(sizeof(char) * 1);
	data->cmd_tab[3] = NULL;
	// for (int i = 0; data->cmd_tab[i]; i++)
	// 	printf("Une ligne cmd tab : %s\n", data->cmd_tab[i]);
	return (SUCCESS);
}