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
**	The purpose of this function is to distinguish the operators. Everything 
** 	else is a WORD. If a WORD contains a '$', it will be typed as VAR.
*/
int	is_an_operator(char *line)
{
	
}

int	tokenize(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{

		i++;
	}
}