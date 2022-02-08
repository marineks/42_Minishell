#include "exec.h"

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

				// tokenizer + parse
				// do your thing
				separate_cmd_lines(&data);
				free(data.line);
			}
			escape_to_brazil(&data);
		}	
		return (0);
}


// 7/02/2022 :main avec ébauche d'un executable pour gerer les multipipes
// int	main(int argc, char **argv, char *envp[])
// {
// 	t_data data;

// 	if (argc != 1)
// 		printf("Command usage: ./minishell\n");
// 	else
// 		{
// 			while (1)
// 			{
// 				readline( "🦊🐆 ~ Minishell :");
// 			init_struct(&data, envp);
// 				if (parse_cmd(&data, argv) == FAILURE)
// 					return (FAILURE);
// 				// if (handle_pipe(argc, argv, &data) == FAILURE)
// 						// {
// 						// 	perror("handle pipe");
// 						// 	return (FAILURE);
// 						// }

// 			}
			
		
// 		}
// 		escape_to_brazil(&data);
// 		return (0);
// }