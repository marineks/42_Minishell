/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:47:16 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/02 15:50:29 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	REDIR_IN 101
	Redirection of input causes the file whose name results from the expansion 
	of word to be opened for reading on file descriptor n, or the standard input
	(file descriptor 0) if n is not specified.

	The general format for redirecting input is: [n]<word
	Source : https://www.gnu.org/software/bash/manual/bash.html#Redirections

	Exemple : sort < mylist.txt => on "sort" par ordre alpha le contenu qui se
				trouve dans "mylist.txt".
				wc -l < test.txt => affiche le nb de lignes dans le fichier test
*/

static void	set_and_display_error(t_cmd *cmd, char *infile)
{
	cmd->infos.error = errno;
	cmd->infos.err_msg = ft_strdup(strerror(errno));
	printf("bash: %s: %s\n", infile, cmd->infos.err_msg);
}

void	parse_redir_in(t_cmd **last_cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*file;
	int		fd;

	tmp = *tk_lst;
	cmd = ft_lstlast_cmd(*last_cmd);
	if (cmd->infos.cmd && ft_strcmp(cmd->infos.cmd, "echo") == SUCCESS)
	{
		*tk_lst = tmp->next->next;
		return ;
	}
	cmd->infos.redir_in = true;
	file = get_relative_path(tmp->next->str);
	fd = open(file, O_RDWR, S_IRWXU);
	if (fd == -1)
		set_and_display_error(cmd, tmp->next->str);
	cmd->infos.fd_in = fd;
	free(file);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
}
