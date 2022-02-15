#include "minishell.h"

/*
*	Expansion is performed on the command line after it has been split  
*	into tokens.There are seven kinds of expansion performed, but we will focus 
*	on the following:
*		parameter and variable expansion
*		command substitution
*		arithmetic expansion
*	
*	After these expansions are performed, quote characters present in the  
*	original word are removed unless they have been quoted themselves.
*/