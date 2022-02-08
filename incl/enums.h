#ifndef ENUMS_H
# define ENUMS_H

# define PROMPT "🦊🐆\033[1;37m ~ Minishell : \033[0m"

enum output {
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = 2,
	TRUE = 3,
	FALSE = 4
};

enum states {
	DEFAULT,
	SIMPLE,
	DOUBLE
};

enum tk_types {
	WORD,		// e.g. abc , "abc" , 'abc'
	VAR,		// e.g. $abc
	PIPE,		// e.g ' | '
	LESSER, 	// e.g '<'
	GREATER, 	// e.g '>'
	DLESSER, 	// e.g '<<' (D stands for double)
	DGREATER, 	// e.g '>>'
	END
};

# endif