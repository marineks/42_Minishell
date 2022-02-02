#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>              /* Definition of O_* constants */
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

enum output {
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = 2,
	TRUE = 3,
	FALSE = 4
};

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef struct	s_pipe 
{	
	char	**cmd;
}				t_pipe;

typedef struct	s_data 
{
	char	**cmd_tab;
	char 	**envp;
	t_pipe	*pipe;

}				t_data;


// EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);
// EXEC --- pipe.c
int		handle_pipe(int argc, char **argv, t_data *data);

// PARSING --- parse_cmd.c
int		parse_cmd(t_data *data, char **argv);

// UTILS --- brazil.c
void	escape_to_brazil(t_data *data);

#endif
