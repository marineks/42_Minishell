#include "minishell.h"

void	print_token(t_token *lst);

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	(void) argv;
	if (argc != 1)
		printf("Command usage: ./minishell\n");
	else
		{
			init_data(&data, envp);
			while (1)
			{
				data.line = readline(PROMPT);
				if (check_exit(data.line) == SUCCESS)
					break;
				add_history(data.line);
				tokenize(&data, data.line);
				// separate_cmd_lines(&data);
				// do your thing
				escape_to_amsterdam(&data);
			}
			escape_to_brazil(&data);
		}	
		return (0);
}
