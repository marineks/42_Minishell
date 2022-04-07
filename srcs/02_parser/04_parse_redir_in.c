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
	
	Problem car avec ECHO ça marche différemment :
https://unix.stackexchange.com/questions/63658/redirecting-the-content-of-a-file-to-the-command-echo)
*/

void	parse_redir_in(t_cmd **last_cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*file;
	int		fd;

	tmp = *tk_lst;
	cmd = *last_cmd;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPARSE - Parse_redir_in function\n");
	if (cmd->infos.cmd && ft_strcmp(cmd->infos.cmd, "echo") == SUCCESS)
	{
		printf("Fd in : %d - Fd out : %d\n", cmd->infos.fd_in, cmd->infos.fd_out);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		*tk_lst = tmp->next->next;
		return ;
	}
	cmd->infos.redir_in = true;
	file = get_relative_path(tmp->next->str);
	fd = open(file, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
	{
		cmd->infos.error = errno;
		cmd->infos.err_msg = ft_strdup(strerror(errno));
		cmd->infos.fd_out = 2;
		printf("N° d'erreur : %d - Erreur : %s - Fd in : %d - Fd out : %d\n",
		cmd->infos.error, cmd->infos.err_msg,  cmd->infos.fd_in, cmd->infos.fd_out);
	}
	else
		cmd->infos.fd_in = fd;
	free(file);
	printf("Fd in : %d\n", cmd->infos.fd_in);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (tmp->next->next && tmp->next->next->type != PIPE)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
}