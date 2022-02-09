#ifndef MINISHELL_H
# define MINISHELL_H

#include "libraries.h"

// EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);
// EXEC --- pipe.c
int		handle_pipe(int argc, char **argv, t_data *data);

// LEXER --- tokenize.c
int		tokenize(t_data *data, char *line);

// PARSING --- parse_cmd.c
int		parse_cmd(t_data *data, char **argv);
// PARSING --- separate_cmd_lines.c
int		separate_cmd_lines(t_data *data);
// PARSING --- split_pipe.c
int		find_pipes(t_data *data, char *line);

// UTILS --- amsterdam.c
void	escape_to_amsterdam(t_data *data);
// UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// UTILS --- exit_whisperer.c
int		check_exit(char *line);
// UTILS --- init_struct.c
int		init_data(t_data *data, char *envp[]);
// UTILS --- token_list_functions.c
t_token	*ft_lstnew_token(char *str, int type, int state);
void	ft_lstadd_back_token(t_token **alst, t_token *new_node);
void	ft_lstdelone_token(t_token *lst, void (*del)(void *));
void	ft_lstclear_token(t_token **lst, void (*del)(void *));

#endif
