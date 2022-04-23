#ifndef EXECVE_FUNCTIONS_H
# define EXECVE_FUNCTIONS_H

# include "structs.h"

// 05_UTILS // execve_functions --- 00_execve_infos.c
t_exec	*get_execve_infos(t_data *data, t_cmd *cmd);
void	free_excve_infos(t_exec *exec_infos);
// 05_UTILS // execve_functions --- 01_convert_env.c
char	**convert_env_copy_to_array(t_env *env);
// 05_UTILS // execve_functions --- 02_get_path.c
char	*grep_path(char *envp[], char *cmd);
// 05_UTILS // execve_functions --- 03_create_cmd_array.c
char	**create_cmd_array(t_cmd *cmd);

#endif