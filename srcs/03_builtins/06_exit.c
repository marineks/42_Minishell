#include "minishell.h"

static bool	is_a_valid_exit(char *flag)
{
	int	i;

	i = 0;
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
	ft_putstr_fd("bash: exit: too many arguments\n", 2);
	g_exit_status = 1;
	return (g_exit_status);
}

static int	numeric_arg_err(char *flag)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(flag, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	g_exit_status = 2;
	return (g_exit_status);
}

/**
 * @brief Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
 * 
 * @param cmd The command line containing the exit
 * @return int The exit status
 */
int	exit_minishell(t_data *data, t_cmd *cmd)
{
	if (cmd->infos.flags)
	{
		if (cmd->infos.flags[1])
			return (too_many_arg_err());
		else if (is_a_valid_exit(cmd->infos.flags[0]) == false)
			return (numeric_arg_err(cmd->infos.flags[0]));
		else
			g_exit_status = ft_atoi(cmd->infos.flags[0]) % 256;
	}
	ft_putstr_fd("exit\n", 1);
	escape_to_brazil(data);
	exit(g_exit_status);
	return (g_exit_status);
}

/* POURQUOI MODULO 256 : 
"The number passed to the _exit()/exit_group() system call
	is of type int, so on Unix-like systems like Linux, typically a 
	32bit integer with values from -2147483648 (-231) to 2147483647 (231-1).

	However, on all systems, when the parent process  uses the wait(), 
	waitpid(), wait3(), wait4() system calls to retrieve it, only the 
	lower 8 bits of it are available (values 0 to 255 (28-1))."
	https://unix.stackexchange.com/questions/418784/what-is-the-min-and-max-values-of-exit-codes-in-linux
*/


/*
Each shell command returns an exit code when it terminates, either successfully 
or unsuccessfully.
By convention, an exit code of zero indicates that the command completed 
successfully, and non-zero means that an error was encountered.

The special variable $? returns the exit status of the last executed command.

When executing a multi-command pipeline, the exit status of the pipeline is that
of the last command.
*/