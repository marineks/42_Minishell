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
				if (tokenize(&data, data.line) == FAILURE)
					printf("tokenize pb\n");
				if (specify(&data.token) == FAILURE)
				{
					escape_to_amsterdam(&data);
					continue;
				}
				expand_tokens(&data, &data.token);
				handle_quotes(&data);
				print_token(data.token);
				// do your thing (parse)
				// do your thing bis (redirections, then exec)
				escape_to_amsterdam(&data);
			}
			escape_to_brazil(&data);
		}	
		return (0);
}
