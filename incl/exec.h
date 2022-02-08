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

typedef struct	s_cmd 
{	
	char			**cmd;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_data 
{
	int		nb_cmd;
	char 	**envp;
	char	*line;
	char	**cmd_lines;
	t_cmd	*cmd;

}				t_data;


// EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);
// EXEC --- pipe.c
int		handle_pipe(int argc, char **argv, t_data *data);

// PARSING --- parse_cmd.c
int		parse_cmd(t_data *data, char **argv);

// PARSING --- separate_cmd_lines.c
int		separate_cmd_lines(t_data *data);
// PARSING --- split_pipe.c
int		find_pipes(t_data *data, char *line);

// UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// UTILS --- init_struct.c
int		init_data(t_data *data, char *envp[]);

// UTILS --- exit_whisperer.c
int		check_exit(char *line);

#endif
