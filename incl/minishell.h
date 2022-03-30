#ifndef MINISHELL_H
# define MINISHELL_H

#include "libraries.h"

// 00_LEXER --- tokenize.c
int		tokenize(t_data *data, char *line);
int		specify(t_token **tk_list);
int		check_ops_rule(t_token **tk_list);

// 01_EXPANDER --- 00_expand_token.c
int		expand_tokens(t_data *data, t_token **tk_list);
// 01_EXPANDER --- 01_retrieve_value.c
char	*retrieve_val(char *str, t_data *data);
// 01_EXPANDER --- 02_identify_var.c
bool	is_var_compliant(char c);
int		count_len_var(char *str);
char	*identify_variable(char *str);
// 01_EXPANDER --- 03_replace_var.c
int		replace_var(t_token **tk_node, char *var_value, int index);
// 01_EXPANDER --- 04_handle_quotes.c
int		count_length(char *str, int count, int i);
int		handle_quotes(t_data *data);
// 01_EXPANDER --- 05_remove_quotes.c
int		remove_quotes(t_token **tk_node);
// 01_EXPANDER --- 06_tokenize_var.c
int		tokenize_var(t_data *data);

// 02_PARSER --- 00_create_cmds.c
void	create_cmds(t_data *data, t_token *token);
// 02_PARSER --- 01_parse_word.c
void	parse_word(t_data *data, t_token **tk_lst);
// 02_PARSER --- 02_fill_flags.c
int		fill_flags(t_token	**tk_node, t_cmd *last_cmd);
// 02_PARSER --- 03_parse_heredoc.c
void	parse_heredoc(t_data *data, t_token **tk_lst);

// 04_EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);

// 05_UTILS --- amsterdam.c
void	escape_to_amsterdam(t_data *data);
// 05_UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// 05_UTILS --- cmd_list_functions.c
t_cmd	*ft_lstnew_cmd(bool value);
void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new_node);
void	ft_lstdelone_cmd(t_cmd *lst, void (*del)(void *));
void	ft_lstclear_cmd(t_cmd **lst, void (*del)(void *));
t_cmd	*ft_lstlast_cmd(t_cmd *cmd);
void	print_cmd(t_cmd *lst);
// 05_UTILS --- exit_whisperer.c
int		check_exit(char *line);
// 05_UTILS --- init_struct.c
int		init_data(t_data *data, char *envp[]);
// 05_UTILS --- token_list_functions.c
t_token	*ft_lstnew_token(char *str, int type, int state);
void	ft_lstadd_back_token(t_token **alst, t_token *new_node);
void	ft_lstdelone_token(t_token *lst, void (*del)(void *));
void	ft_lstclear_token(t_token **lst, void (*del)(void *));
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);
void	print_token(t_token *lst);

#endif
