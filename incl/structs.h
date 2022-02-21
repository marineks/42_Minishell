#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

typedef struct	s_token 
{	
	char			*str;			// e.g. "foo bar baz" => ALWAYS MALLOC??
	int				type;			// e.g. WORD
	int				state;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_pipe 
{	
	t_list	*lst;
	char 	**cmd;
	int 	nb_pipes;

}				t_pipe;

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
	t_pipe	*pipe;
	char	**cmd_lines;
	t_token	*token;
	char	**cmd_tab;
	t_cmd	*cmd;

}				t_data;

#endif