/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:05:54 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 16:05:55 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	APPENDING REDIR_OUT 101
	Redirection of output in this fashion causes the file whose name results 
	from the expansion of word to be opened for appending on file descriptor n, 
	or the standard output (file descriptor 1) if n is not specified. 
	If the file does not exist it is created.

	The general format for appending output is: [n]>>word.
	Source : https://www.gnu.org/software/bash/manual/bash.html#Redirections

	Focus on the O_APPEND flag of the function open() :
	" O_APPEND
              The file is opened in append mode.  Before each write(2),
              the file offset is positioned at the end of the file, as
              if with lseek(2).  The modification of the file offset and
              the write operation are performed as a single atomic step."
	Source : man 2 open
*/

/**
 * @brief When encountering a APPEND typed token ('>>'), this function :
 * 			- sets the boolean cmd->infos.redir_out to TRUE;
 * 			- If the next token is valid, it opens the output file (or creates
 * 			  it if it does not exist) with the correct relative path retrieved
 * 			  beforehand and appends the previous token(s) to the end of the
 * 			  output file.
 * 			- With the fd information, completes the necessary fields of 
 * 			  cmd->infos; i.e. fd_out and potentially error and err_msg.
 * 
 * @param last_cmd A pointer to the address of the last command structure.
 * @param tk_lst A pointer to the address of the current token node.
 * 	- 
 */
void	parse_append(t_cmd **last_cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*file;
	int		fd;

	tmp = *tk_lst;
	cmd = ft_lstlast_cmd(*last_cmd);
	cmd->infos.redir_out = true;
	file = get_relative_path(tmp->next->str);
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		cmd->infos.error = errno;
		cmd->infos.err_msg = ft_strdup(strerror(errno));
	}
	cmd->infos.fd_out = fd;
	free(file);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
}
