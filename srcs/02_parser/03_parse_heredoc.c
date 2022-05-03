/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:13:56 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/03 15:11:38 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_line_in_submode(char *line, char *delimiter, char *str)
{
	while (line)
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == SUCCESS)
			break ;
		if (!str)
			str = ft_strdup(line);
		else
		{
			str = ft_strjoin(str, "\n");
			str = ft_strjoin(str, line);
		}	
	}
	if (str == NULL)
		return (ft_strdup("\n"));
	str = ft_strjoin(str, "\n");
	free(line);
	return (str);
}

static char	*stock_buffer(t_token **tk_lst)
{
	t_token	*tmp;
	char	*line;
	char	*str;
	char	*delimiter;

	tmp = *tk_lst;
	line = (char *)malloc(sizeof(char));
	delimiter = tmp->next->str;
	str = get_line_in_submode(line, delimiter, NULL);
	return (str);
}

static char	*heredoc_child_proc(int *pipe_fds, t_token **tk_lst, t_data *data)
{
	char	*buffer;

	interpret_signal(HEREDOC_MODE, NULL);
	close(pipe_fds[READ]);
	buffer = stock_buffer(tk_lst);
	write(pipe_fds[WRITE], buffer, ft_strlen(buffer) + 1);
	close(pipe_fds[WRITE]);
	free(buffer);
	escape_to_brazil(data);
	exit(g_exit_status);
}

static void	heredoc_parent_proc(t_data *data, int *pipe_fds)
{
	wait(NULL);
	close(pipe_fds[WRITE]);
	data->cmd->infos.fd_in = pipe_fds[READ];
}

int	parse_heredoc(t_data *data, t_token **tk_lst)
{
	pid_t	pid;
	int		pipe_fds[2];
	t_token	*tmp;

	data->cmd->infos.redir_in = true;
	if (pipe(pipe_fds) == -1)
		return (FAILURE);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	else if (pid == 0)
		heredoc_child_proc(pipe_fds, tk_lst, data);
	else
		heredoc_parent_proc(data, pipe_fds);
	tmp = *tk_lst;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*tk_lst = tmp;
	return (SUCCESS);
}
