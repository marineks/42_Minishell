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

// static char	*get_absolute_path(char **env, char *file_to_open)
// {
// 	char	*path;
// 	int		i;

// 	path = ft_strdup("PWD");
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strcmp(path, env[i]) == SUCCESS)
// 			break;
// 		i++;
// 	}
// 	path = ft_strjoin(*env + (i + 4), "/");
// 	path = ft_strjoin(path, file_to_open);
// 	printf("PARSING - Get_absolute_path function return : %s\n", path);
// 	return (path);
// }

char	*get_relative_path(char *file_to_open)
{
	char *path;
	char *res;

	path = ft_strdup("./");
	res = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", res);
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
void	parse_redir_out(t_data *data, t_cmd **last_cmd, t_token **tk_lst)
{
	t_token	*tmp;
	t_cmd	*cmd;
	char	*file;
	int		fd;

	(void) data;
	tmp = *tk_lst;
	cmd = ft_lstlast_cmd(*last_cmd);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPARSE - Parse_redir_out function\n");
	cmd->infos.redir_out = true;
	// char *test = get_absolute_path(data->envp, tmp->next->str);
	// printf("test : %s\n", test);
	file = get_relative_path(tmp->next->str);
	fd = open(file, O_CREAT | O_RDWR, S_IRWXU); // rajouter O_TRUNC
	if (fd == -1)
	{
		cmd->infos.error = errno;
		cmd->infos.err_msg = ft_strdup(strerror(errno));
		cmd->infos.fd_out = 2;
		printf("N° d'erreur : %d - Erreur : %s - Fd : %d\n", cmd->infos.error,\
	cmd->infos.err_msg, cmd->infos.fd_out);
	}
	else
	// if cmd->infos.fd_out != 0 
		// close(cmd->infos.fd_out)
		cmd->infos.fd_out = fd;
	free(file);
	printf("Fd out : %d\n", cmd->infos.fd_out);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	if (tmp->next->next && tmp->next->next->type != PIPE)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
}

/*
A noter : si on fait ls > test2.txt puis echo coucou > test2.txt
le nouveau contenu va écraser le précédent

cmd REDIR_OUT OUTPUT_FILE word
exemple : grep test > test.txt test1.txt
En gros, si y a un word après l'OUTPUT_FILE il va dans le echo, pas dans la redir

ATTENTION !!!!!!
SI LINE COMMENCE PAR UN REDIR IL FAUT CREER LA LISTE CHAINEE ! 
DU COUP FAIRE CONDITION existence cmd + FONCTION POUR PALLIER CA
*/