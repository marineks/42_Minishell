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


/*
** ROAD MAP LEXER :
**	- loop through the user's line
**	- if the character is not a metacharacter, continue
**	- else copy the line until the metacharacter in a node
**	- put the metacharacter in the next node
**	- repeat until the last element, which will be marked as END
*/



/*
**	The purpose of this function is to distinguish the operators. Everything 
** 	else is a WORD. NB: If a WORD contains a '$', it will be typed as VAR.
*/
int	is_an_operator(char c)
{
	if (c == '|' || c == '<' || c =='>' || c == '>>' || c == '<<') 
		return (TRUE);
	else
		return (FALSE);
}

int	mark_as_word(t_data *data, char *line, int i, int index)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * index);
	while (i < index)
	{
		str[i] = line[i];
		i++;
	}
	printf("mark as word > %s\n", str);
	ft_lstadd_back(&data->token, ft_lstnew(str)); // penser à free la t_list token dans escape to brazil
	data->token->type = WORD;
	data->token->index = ft_lstsize(data->token) - 1;
	free(str);
	return (SUCCESS);
}

int	tokenize(t_data *data, char *line)
{
	int	i;
	int start;

	init_token_struct(data);
	i = 0;
	start = 0;
	while (line[i])
	{
		if (is_an_operator(line[i]) == TRUE)
		{
			mark_as_word(data, line, start, i); // ex: ls | pwd  => mark ls as a WORD
			identify_operator(data, line[i]); // ex : ls | pwd => identify the operator | and put its correct type (PIPE)
			// ATTENTION LA JE PENSE COMME SI LE METACHAR N'ETAIT QU'UN CHAR MAIS ON A CE CAS : '>>'
		}
		// cas ou on a un dernier groupe a identifier puis l'EOL à gérer (cas du pwd dans l'ex plus haut)
		i++;
		start = i;
	}
	
}