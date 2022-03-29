#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

typedef struct	s_token 
{	
	char			*str;			// e.g. "foo bar baz" => ALWAYS MALLOC??
	int				type;			// e.g. WORD
	int				state;
	// bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_pipe 
{	
	t_list	*lst;
	char 	**cmd;
	int 	nb_pipes;
}				t_pipe;

typedef struct	s_infos 
{	
	char			*cmd;
	char			**flags;
	char			**arg_env;
	bool			builtin;
	bool			redir_in;
	bool			redir_out;
	int				fd_in;
	int				fd_out;
	int				error;
}				t_infos;

typedef struct	s_cmd
{
	bool			is_pipe;
	t_infos			infos;
	struct	s_cmd	*left;
	struct	s_cmd	*right;
}				t_cmd;

typedef struct	s_data 
{
	int		nb_cmd;
	char 	**envp;
	char	*line;
	t_pipe	*pipe;
	char	**cmd_lines;
	char	**cmd_tab;
	t_token	*token;
	t_cmd	*cmd;
}				t_data;

#endif