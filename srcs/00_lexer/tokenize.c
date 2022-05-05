/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:54:12 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/05 19:12:47 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 *	@brief Tokenize splits the command line issued by the user.
 *	@param data - our main structure that will host the chained list of the
 *				   the tokens in data->token.
 *	@param line - the string that will be split
 *
 *	This is the first part of the lexer, where we divide the line into two
 *	big types of tokens : WORDS and SEPARATORS (for instance pipes, redir.,
 *	heredocs and blanks).
 *	This function :
 *	- checks each character of line to find whether there is a separator
 *	- in order to do so, we first make sure that the separator is not inhibited
 *	  by quotes (states : SIMPLE or DOUBLE)
 */
int	tokenize(t_data *data, char *line)
{
	int	i;
	int	end;
	int	start;
	int	state;

	i = 0;
	start = 0;
	end = ft_strlen(line);
	state = DEFAULT;
	while (i <= end)
	{
		state = which_state(state, line, i);
		if (state == DEFAULT)
			start = stock_as_word_or_sep(&i, line, start, data);
		i++;
	}
	if (state != DEFAULT)
	{
		free(data->line);
		return (printf("Minishell : syntax error : the quotes are unclosed\n"));
	}	
	return (SUCCESS);
}
