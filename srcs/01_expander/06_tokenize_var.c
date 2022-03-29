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

static int	create_empty_str_in_new_node(t_token **tk_lst)
{
	char *str;

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (FAILURE);
	str[0] = '\0';
	ft_lstadd_back_token(tk_lst, ft_lstnew_token(str, VAR, DEFAULT));
	return (SUCCESS);
}

static t_token	*split_var(char *str, t_token *tk_lst)
{
	int		i;
	int		start;
	char	*new_word;
	
	i = 0;
	if (!str[i])
		create_empty_str_in_new_node(&tk_lst);
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

void	set_new_lst_to_true(t_token **new_lst)
{
	t_token *tmp;

	tmp = *new_lst;
	while (tmp)
	{
		tmp->join = true;
		tmp = tmp->next;
	}
}

int	tokenize_var(t_data *data)
{
	t_token	*tmp;
	t_token	*new_lst;
	t_token	*tk_lst;

	tmp = data->token;
	new_lst = NULL;
	tk_lst = NULL;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			new_lst = split_var(tmp->str, tk_lst);
			print_token(data->token);
			if (tmp->join == true)
				set_new_lst_to_true(&new_lst);
			tmp = insert_lst_between(&data->token, tmp, new_lst);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
