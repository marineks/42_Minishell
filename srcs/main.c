#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	(void) argv;
	if (*envp == NULL)
	{
		ft_putstr_fd("Pas de env pas de minishell\n", 2);
		return (-1);
	}
	g_exit_status = 0;
	ft_memset(&data, 0, sizeof(t_data));

	if (argc != 1)
		printf("Command usage: ./minishell\n");
	else
		{
			init_data(&data, envp);
			while (1)
			{
				interpret_signal(BASIC, NULL);
				data.line = readline(PROMPT);
				if (data.line == NULL)
				{
					write(1, "exit\n", 5);
					escape_to_brazil(&data);
					exit(130);
				}
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
				tokenize_var(&data);
				// print_token(data.token);
				create_cmds(&data, data.token);
				// print_cmd(data.cmd);
				if (data.cmd)
					exec(&data);
				escape_to_amsterdam(&data);
			} 
			escape_to_brazil(&data);
		}	
		return (0);
}
