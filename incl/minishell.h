#ifndef MINISHELL_H
# define MINISHELL_H

#include "libraries.h"

// 00_LEXER --- tokenize.c
int		tokenize(t_data *data, char *line);
int		specify(t_token **tk_list);
int		check_ops_rule(t_token **tk_list);

// 01_EXPANDER --- expand_token.c
int		expand_tokens(t_data *data, t_token **tk_list);
// 01_EXPANDER --- handle_quotes.c
int		handle_quotes(t_data *data);
// 01_EXPANDER --- retrieve_value.c
int		replace_value(t_token *tk_node, t_data *data);

// 04_EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);

// 05_UTILS --- amsterdam.c
void	escape_to_amsterdam(t_data *data);
// 05_UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// 05_UTILS --- exit_whisperer.c
int		check_exit(char *line);
// 05_UTILS --- init_struct.c
int		init_data(t_data *data, char *envp[]);
// 05_UTILS --- token_list_functions.c
t_token	*ft_lstnew_token(char *str, int type, int state);
void	ft_lstadd_back_token(t_token **alst, t_token *new_node);
void	ft_lstdelone_token(t_token *lst, void (*del)(void *));
void	ft_lstclear_token(t_token **lst, void (*del)(void *));
void	print_token(t_token *lst);

#endif
