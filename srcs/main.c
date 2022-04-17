#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_data data;

	(void) argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (argc != 1)
		printf("Command usage: ./minishell\n");
	else
		{
			init_data(&data, envp);
			while (1)
			{
				data.line = readline(PROMPT);
				// if (check_exit(data.line) == SUCCESS)
				// {
				// 	printf("l'exit status : %d\n", g_exit_status);
				// 	break;
				// }
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
				print_token(data.token);
				create_cmds(&data, data.token);
				// get_pwd(data.cmd, data.env_copy);
				// get_env(data.cmd, data.env_copy);
				// get_echo(data.cmd);
				// export_new_var(data.cmd, &data.env_copy);
				// printf("je retourne dans le main et après ça coupe sans faire get env\n");
				// get_env(data.cmd, &data.env_copy);
				if (ft_strcmp(data.cmd->infos.cmd, "exit") == SUCCESS)
					exit_minishell(data.cmd);
				escape_to_amsterdam(&data);
			} 
			escape_to_brazil(&data);
		}	
		return (0);
}
