/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:18:14 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 14:23:39 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_state(int state, char *line, int i)
{
	if (line[i] == '\'' && state == DEFAULT)
		state = SIMPLE;
	else if (line[i] == '\"' && state == DEFAULT)
		state = DOUBLE;
	else if (line[i] == '\'' && state == SIMPLE)
		state = DEFAULT;
	else if (line[i] == '\"' && state == DOUBLE)
		state = DEFAULT;
	return (state);
}

int	is_separator(char *line, int i)
{
	if (((line[i] > 8 && line[i] < 14) || line[i] == 32))
		return (BLANK);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	else if (line[i] == '<')
		return (REDIR_IN);
	else if (line[i] == '>')
		return (REDIR_OUT);
	else if (line[i] == '\0')
		return (END);
	else
		return (0);
}

int	stock_word(t_token **tk_list, char *line, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (FAILURE);
	while (start < index)
	{
		word[i] = line[start];
		start++;
		i++;
	}
	word[i] = '\0';
	ft_lstadd_back_token(tk_list, ft_lstnew_token(word, WORD, DEFAULT));
	return (SUCCESS);
}

int	stock_separator(t_token **tk_list, char *line, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = (char *)malloc(sizeof(char) * 3);
		if (!sep)
			return (FAILURE);
		while (i < 2)
			sep[i++] = line[index++];
		sep[i] = '\0';
		ft_lstadd_back_token(tk_list, ft_lstnew_token(sep, type, DEFAULT));
	}
	else
	{
		sep = (char *)malloc(sizeof(char) * 2);
		if (!sep)
			return (FAILURE);
		while (i < 1)
			sep[i++] = line[index++];
		sep[i] = '\0';
		ft_lstadd_back_token(tk_list, ft_lstnew_token(sep, type, DEFAULT));
	}
	return (SUCCESS);
}

int	stock_as_word_or_sep(int *i, char *line, int start, t_data *data)
{
	int	type;

	type = is_separator(line, (*i));
	if (type)
	{
		if ((*i) != 0 && is_separator(line, (*i) - 1) == 0)
			stock_word(&data->token, line, (*i), start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == REDIR_IN || type == REDIR_OUT || type == END)
		{
			stock_separator(&data->token, line, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}
