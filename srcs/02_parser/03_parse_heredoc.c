#include "minishell.h"

void	parse_heredoc(t_data *data, t_token **tk_lst)
{
	(void)data;
	t_token	*tmp;
	char	*line;
	char	*delimiter;

	tmp = *tk_lst;
	line = (char *)malloc(sizeof(char));
	delimiter = tmp->next->str;
	while (line)
	{
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!(ft_strncmp(line, delimiter, (ft_strlen(line) - 1))))
			break;
	}
	free(line);
	tmp = tmp->next->next;
	*tk_lst = tmp;
}