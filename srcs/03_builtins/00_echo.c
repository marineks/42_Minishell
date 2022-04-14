#include "minishell.h"

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
	if (ft_strcmp("-n", cmd->infos.flags[i]) == SUCCESS)
	{
		print_newline = false;
		i++;
	}
	while (cmd->infos.flags[i])
	{
		len = ft_strlen(cmd->infos.flags[i]);
		write(cmd->infos.fd_out, cmd->infos.flags[i], len);
		write(cmd->infos.fd_out, " ", 1);
		i++;
	}
	if (print_newline == true)
		write(cmd->infos.fd_out, "\n", 1);
}