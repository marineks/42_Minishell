#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	(void) argv;
	if (argc != 1)
		printf("Command usage: ./minishell\n");
	else
		{
			
			while (1)
			{
				init_data(&data, envp); 
				data.line = readline(PROMPT);
				if (check_exit(data.line) == SUCCESS)
					break;
				add_history(data.line);
				// tokenizer + parse
				separate_cmd_lines(&data);
				// do your thing
				free(data.line);
			}
			escape_to_brazil(&data);
		}	
		return (0);
}
