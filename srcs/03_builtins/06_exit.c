/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:58:53 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 17:01:28 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	EXIT 101
	Each shell command returns an exit code when it terminates, either 
	successfully or unsuccessfully.
	By convention, an exit code of zero indicates that the command completed 
	successfully, and non-zero means that an error was encountered.

	The special variable $? returns the exit status of the last executed 
	command.

	When executing a multi-command pipeline, the exit status of the pipeline is 
	that of the last command.
*/

static bool	is_a_valid_exit(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-' || flag[i] == '+')
		i++;
	while (flag[i])
	{
		if (!ft_isdigit(flag[i]))
			return (false);
		i++;
	}
	if (ft_strlen(flag) >= 20)
		return (false);
	return (true);
}

static int	too_many_arg_err(void)
{
	ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
	g_exit_status = 1;
	return (g_exit_status);
}

static void	numeric_arg_err(t_data *data, char *flag)
{
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(flag, STDERR_FILENO);
	ft_putstr_fd(" : numeric argument required\n", STDERR_FILENO);
	g_exit_status = 2;
	escape_to_brazil(data);
	exit(g_exit_status);
}

/**
 * @brief Exits the shell with a status of N.  If N is omitted, the exit status
 * is that of the last command executed.
 * 
 * 	WHY MODULO 256 : 
 * 	"The number passed to the _exit()/exit_group() system call
 * 	is of type int, so on Unix-like systems like Linux, typically a 
 * 	32bit integer with values from -2147483648 (-231) to 2147483647 (231-1).
 * 	However, on all systems, when the parent process  uses the wait(), 
 * 	waitpid(), wait3(), wait4() system calls to retrieve it, only the 
 * 	lower 8 bits of it are available (values 0 to 255 (28-1))."
 * 	https://unix.stackexchange.com/questions/418784/what-is-the-min-and-max-\
 * 	values-of-exit-codes-in-linux
 * 
 * @param cmd The command line containing the exit
 * @return int The exit status
 */
int	exit_minishell(t_data *data, t_cmd *cmd)
{
	if (cmd->infos.flags)
	{
		if (is_a_valid_exit(cmd->infos.flags[0]) == false)
			numeric_arg_err(data, cmd->infos.flags[0]);
		else if (cmd->infos.flags[1])
			return (too_many_arg_err());
		else
			g_exit_status = ft_atoi(cmd->infos.flags[0]) % 256;
	}
	ft_putstr_fd("exit\n", 1);
	escape_to_brazil(data);
	exit(g_exit_status);
	return (g_exit_status);
}
