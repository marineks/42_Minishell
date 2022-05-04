/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:09:00 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 11:36:17 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void	set_up_readline(t_data *data)
{
	interpret_signal(BASIC, NULL);
	data->line = readline(PROMPT);
	if (data->line == NULL)
	{
		write(1, "exit\n", 5);
		escape_to_brazil(data);
		exit(130);
	}
	add_history(data->line);
	if (tokenize(data, data->line) == FAILURE)
		printf("Issue in the tokenization\n");
}

static void	parse_and_execute(t_data *data)
{
	expand_tokens(data, &data->token);
	handle_quotes(data);
	tokenize_var(data);
	create_cmds(data, data->token);
	if (data->cmd)
		exec(data);
	escape_to_amsterdam(data);
}

static int	check_envp_and_init(char *envp[], t_data *data)
{
	if (*envp == NULL)
	{
		ft_putstr_fd(ENV_MSG, STDERR_FILENO);
		return (-1);
	}
	g_exit_status = 0;
	ft_memset(data, 0, sizeof(t_data));
	return (SUCCESS);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;

	(void) argv;
	check_envp_and_init(envp, &data);
	if (argc != 1)
		printf("Command usage: ./minishell\n");
	else
	{
		init_data(&data, envp);
		while (1)
		{
			set_up_readline(&data);
			if (specify(&data.token) == FAILURE)
			{
				escape_to_amsterdam(&data);
				continue ;
			}
			parse_and_execute(&data);
		}
		escape_to_brazil(&data);
	}	
	return (0);
}
