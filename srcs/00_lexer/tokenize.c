
#include "minishell.h"

void	print_token(t_token *lst);
/*
**	THE POINT OF A LEXER_
**	Roughly speaking, the shell reads its input and divides the input into 
**	words and operators, employing the quoting rules to select which meanings 
**	to assign various words and characters.
**	
**	The shell then parses these tokens into commands and other constructs, 
**	removes the special meaning of certain words or characters, expands others, 
**	redirects input and output as needed, executes the specified command, 
**	waits for the command’s exit status, and makes that exit status available 
**	for further inspection or processing.
*/

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
		return (DLESSER);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (DGREATER);
	else if (line[i] == '<')
		return (LESSER);
	else if (line[i] == '>')
		return (GREATER);
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
	int i;
	char *sep;

	i = 0;
	if (type == DGREATER || type == DLESSER)
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

/*
**	Tokenize loops through the command line issued by the user.
**	This is the first part of the lexer, where we divide the line into two
**	big types of tokens : WORDS and SEPARATORS (for instance pipes, redir.,
**	heredocs and blanks).
**	This function :
**	- checks each character of line to find whether there is a separator
**	- in order to do so, we first make sure that the separator is not inhibited
**	  by quotes (states : SIMPLE or DOUBLE)
*/
int	tokenize(t_data *data, char *line)
{
	int	i;
	int end;
	int start;
	int	type;
	int	state;

	i = 0;
	start = 0;
	end = ft_strlen(line);
	state = DEFAULT;
	while (i <= end)
	{
		state = which_state(state, line, i);
		if (state == DEFAULT)
		{
			type = is_separator(line, i);
			if (type) 
			{
				// Fonction qui récupère le WORD avant le separateur
				if (i != 0 && is_separator(line, i - 1) == 0)
					stock_word(&data->token, line, i, start);
				if (type == DGREATER || type == DLESSER) // RENVOIE LE TYPE
				{
					// Fonction qui ajoute le node du séparateur et le type
					stock_separator(&data->token, line, i, type);
					i++;
				}
				else if (type == BLANK) // separe mais ne stock le separateur
					printf("blank\n");
				else // Fonction qui ajoute le node et le type du separateur
					stock_separator(&data->token, line, i, type);
				start = i + 1;
			}
		}
		i++;
	}
	if (state != DEFAULT)
	{
		printf("Unclosed quotes error\n");
		return (FAILURE);
	}
	print_token(data->token);
	return (SUCCESS);
}