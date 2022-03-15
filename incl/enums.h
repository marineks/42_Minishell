#ifndef ENUMS_H
# define ENUMS_H

# define PROMPT "🦊🐆\033[1;37m ~ Minishell : \033[0m"

enum e_output {
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = 2,
	TRUE = 3,
	FALSE = 4
};

enum e_states {
	DEFAULT,
	SIMPLE,
	DOUBLE
};

enum e_tk_types {
	BLANK = 1,		// whites spaces
	WORD,		// e.g. abc , "abc" , 'abc'
	VAR,		// e.g. $abc
	PIPE,		// e.g ' | '
	REDIR_IN, 	// e.g '<'
	REDIR_OUT, 	// e.g '>'
	HEREDOC, 	// e.g '<<' (D stands for double)
	DGREATER, 	// e.g '>>'
	END
};

# endif