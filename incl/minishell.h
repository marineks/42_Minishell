#ifndef MINISHELL_H
# define MINISHELL_H

#include "libraries.h"
int	g_exit_status;

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
void	parse_word(t_cmd **cmd, t_token **tk_lst);
// 02_PARSER --- 02_fill_flags.c
int		fill_flags(t_token	**tk_node, t_cmd *last_cmd);
// 02_PARSER --- 03_parse_heredoc.c
int	parse_heredoc(t_data *data, t_token **tk_lst);
// 02_PARSER --- 04_parse_redir_in.c
void	parse_redir_in(t_cmd **last_cmd, t_token **tk_lst);
// 02_PARSER --- 05_parse_redir_out.c
char	*get_relative_path(char *file_to_open);
void	parse_redir_out(t_data *data, t_cmd **last_cmd, t_token **tk_lst);
// 02_PARSER --- 06_parse_append.c
void	parse_append(t_cmd **last_cmd, t_token **tk_lst);
// 02_PARSER --- 07_parse_pipe.c
void	parse_pipe(t_cmd **cmd, t_token **tk_lst);

// 03_BUILTINS --- 00_get_echo.c
void	get_echo(t_cmd *cmd);
// 03_BUILTINS --- 02_get_pwd.c
void	get_pwd(t_cmd *cmd, t_env *env);
// 03_BUILTINS --- 03_export_new_var.c
int		export_new_var(t_cmd *cmd, t_env **env);
// 03_BUILTINS --- 05_get_env.c
void	get_env(t_cmd *cmd, t_env **env);
// 03_BUILTINS --- 06_exit_minishell.c
int		exit_minishell(t_data *data, t_cmd *cmd);

// 04_EXEC --- get_path.c
char	*grep_path(char *envp[], char *cmd);

// 05_UTILS --- amsterdam.c
void	escape_to_amsterdam(t_data *data);
// 05_UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// 05_UTILS --- exit_whisperer.c
int		check_exit(char *line);
// 05_UTILS --- init_struct.c
char	*call_me_by_your_name(char *line);
char	*call_me_by_your_value(char *line);
int		init_data(t_data *data, char *envp[]);


#endif
