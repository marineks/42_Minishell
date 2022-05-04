/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_parse_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:05:13 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 13:13:56 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	REDIR_OUT 101
	Redirection of output causes the file whose name results from the expansion 
	of word to be opened for writing on file descriptor n, or the standard 
	output (file descriptor 1) if n is not specified. If the file does not exist
	it is created; if it does exist it is truncated to zero size.

	The general format for redirecting output is: [n]>[|]word
	Source : https://www.gnu.org/software/bash/manual/bash.html#Redirections
*/

char	*get_relative_path(char *file_to_open)
{
	char	*path;
	char	*res;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	res = ft_strjoin(path, file_to_open);
	return (res);
}

/**
 * @brief When encountering a REDIR_OUT typed token ('>'), this function :
 * 			- sets the boolean cmd->infos.redir_out to TRUE;
 * 			- If the next token is valid, it opens the output file (or creates
 * 			  it if it does not exist) with the correct relative path retrieved
 * 			  beforehand;
 * 			- With the fd information, completes the necessary fields of 
 * 			  cmd->infos; i.e. fd_out and potentially error and err_msg.
 * 
 * @param last_cmd A pointer to the address of the last command structure.
 * @param tk_lst A pointer to the address of the current token node.
 * 	- 
 */
void	parse_redir_out(t_cmd **last_cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*file;
	int		fd;

	tmp = *tk_lst;
	cmd = ft_lstlast_cmd(*last_cmd);
	cmd->infos.redir_out = true;
	file = get_relative_path(tmp->next->str);
	if (cmd->infos.fd_in != -1)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fd == -1)
		{
			cmd->infos.error = errno;
			cmd->infos.err_msg = ft_strdup(strerror(errno));
		}
		cmd->infos.fd_out = fd;
	}
	free(file);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
}
