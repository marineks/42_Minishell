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

// UTILS --- brazil.c
void	escape_to_brazil(t_data *data);
// UTILS --- init_struct.c
int		init_data(t_data *data, char *envp[]);
int		init_token_struct(t_data *data);
// UTILS --- exit_whisperer.c
int		check_exit(char *line);

#endif
