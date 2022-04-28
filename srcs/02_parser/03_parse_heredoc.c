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
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == SUCCESS)
			break;
		if (!str)
			str = ft_strdup(line);
		else
			str = ft_strjoin(str, line);
	}
	free(line);
	return (str);
}

int parse_heredoc(t_data *data, t_token **tk_lst)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		status;
	char	*buffer;
	t_token	*tmp;
	t_data	heredoc;

	data->cmd->infos.redir_in = true;
	if (pipe(pipe_fds) == -1)
	{
		perror("Pipe");
		return (FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (FAILURE);
	}
	else if (pid == 0)
	{
		ft_memset(&heredoc, 0, sizeof(t_data));
		init_data(&heredoc, convert_env_copy_to_array(data->env_copy));
		interpret_signal(HEREDOC_MODE, NULL);
		close(pipe_fds[READ]);
		buffer = stock_buffer(tk_lst);
		tokenize(&heredoc, buffer);
		specify(&heredoc.token);
		expand_tokens(&heredoc, &heredoc.token);
		handle_quotes(&heredoc);
		free(buffer);
		buffer = NULL;
		tmp = heredoc.token;
		while (tmp->next)
		{
			if (!buffer)
				buffer = ft_strdup(tmp->str);
			else
				buffer = ft_strjoin(buffer, tmp->str);
			buffer = ft_strjoin(buffer, "\n");
			tmp = tmp->next;
		}
		write(pipe_fds[WRITE], buffer, ft_strlen(buffer) + 1);
		close(pipe_fds[WRITE]);
		free(buffer);
		free_double_array(heredoc.envp);
		escape_to_brazil(&heredoc);
		escape_to_brazil(data);
		exit(g_exit_status);
	}
	else
	{
		wait(NULL);
		close(pipe_fds[WRITE]);
		data->cmd->infos.fd_in = pipe_fds[READ];
	}
	tmp = *tk_lst;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
	return (SUCCESS);
}
