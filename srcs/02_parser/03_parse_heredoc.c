#include "minishell.h"

static char *stock_buffer(t_token **tk_lst)
{
	t_token	*tmp;
	char	*line;
	char	*str;
	char	*delimiter;

	tmp = *tk_lst;
	line = (char *)malloc(sizeof(char));
	delimiter = tmp->next->str;
	str = NULL;
	while (line)
	{
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!str)
			str = ft_strdup(line);
		else
			str = ft_strjoin(str, line);
		if (!(ft_strncmp(line, delimiter, (ft_strlen(line) - 1))))
			break;
	}
	free(line);
	return (str);
}

// TO DO : attention à la str statique, trouver un moyen d'allouer la bonne mémoire
int parse_heredoc(t_data *data, t_token **tk_lst)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		status;
	char	str[1000];
	char	*buffer;
	t_token	*tmp;

	tmp = *tk_lst;
	data->cmd->infos.redir_in = true;
	if (pipe(pipe_fds) == -1)
	{
		perror("Pipe");
		return (FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (FAILURE);
	}
	else if (pid == 0)
	{
		close(pipe_fds[READ]);
		buffer = stock_buffer(tk_lst);
		printf("Heredoc | Buffer récupéré : %s\n", buffer);
		write(pipe_fds[WRITE], buffer, ft_strlen(buffer) + 1);
		close(pipe_fds[WRITE]);
		free(buffer);
		exit(1);
	}
	else
	{
		close(pipe_fds[WRITE]);
		waitpid(pid, &status, 0);
		read(pipe_fds[READ], str, 1000);
		data->cmd->infos.fd_in = pipe_fds[READ];
		close(pipe_fds[READ]);
	}
	printf("Heredoc | fd_in récupéré : %d\n", data->cmd->infos.fd_in);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
	return (SUCCESS);
}
