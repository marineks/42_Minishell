#include "minishell.h"

static int	find_str(char *haystack, char *needle)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (haystack[i + 1] && haystack[i + 1] == needle[1])
				return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

static char	*replace_exit_status(char *flags)
{
	char	*exit_value;
	char	*new_str;
	int		i;
	int		j;
	int		len;

	exit_value = ft_itoa(g_exit_status);
	len = ft_strlen(exit_value) + 1;
	new_str = malloc(sizeof(char) * (ft_strlen(flags) - 2 + len));
	i = -1;
	while (flags[++i] && flags[i] != '$')
		new_str[i] = flags[i];
	len = i + 2;
	j = 0;
	while (exit_value[j])
		new_str[i++] = exit_value[j++];
	j = 0;
	while (flags[len])
		new_str[i++] = flags[len++];
	new_str[i] = '\0';
	free(flags);
	free(exit_value);
	return (new_str);
}

static int	check_nl(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) < 2 || str[0] != '-' || str[1] != 'n')
		return (FAILURE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief The command "echo" prints a string. "echo -n" does not print the final
 * 		  newline. 
 * 
 * @param cmd Our node of command containing all the informations pertaining 
 * 			  to the current command (flags, redirections...).
 */
void	get_echo(t_cmd *cmd)
{
	bool	print_newline;
	int		len;
	int		i;

	print_newline = true;
	i = 0;
	if (cmd->infos.flags && check_nl(cmd->infos.flags[i]) == SUCCESS)
	{
		print_newline = false;
		i++;
	}
	while (cmd->infos.flags && cmd->infos.flags[i])
	{
		if (find_str(cmd->infos.flags[i], "$?") == SUCCESS)
			cmd->infos.flags[i] = replace_exit_status(cmd->infos.flags[i]);
		len = ft_strlen(cmd->infos.flags[i]);
		write(cmd->infos.fd_out, cmd->infos.flags[i], len);
		write(cmd->infos.fd_out, " ", 1);
		i++;
	}
	if (print_newline == true)
		write(cmd->infos.fd_out, "\n", 1);
	g_exit_status = 0;
}
