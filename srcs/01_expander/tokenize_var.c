#include "minishell.h"

static char	*copy_word(char *str, int end, int start)
{
	char	*new_word;
	int		i;

	i = 0;
	new_word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!new_word)
		return (NULL);
	while (start < end)
	{
		new_word[i] = str[start];
		i++;
		start++;
	}
	new_word[i] = '\0';
	return (new_word);
}

static t_token	*split_var(char *str)
{
	int		i;
	int		start;
	char	*new_word;
	t_token	*tk_lst;

	i = 0;
	tk_lst = NULL;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			start = i;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_word = copy_word(str, i, start);
		ft_lstadd_back_token(&tk_lst, ft_lstnew_token(new_word, VAR, DEFAULT));
	}
	return (tk_lst);
}

int	tokenize_var(t_data *data)
{
	t_token	*tmp;
	t_token	*new_lst;

	tmp = data->token;
	new_lst = NULL;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			new_lst = split_var(tmp->str);
			tmp = insert_lst_between(&data->token, tmp, new_lst);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
