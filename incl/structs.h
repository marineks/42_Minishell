/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:59:26 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 13:01:07 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"

typedef struct s_token
{	
	char			*str;
	int				type;
	int				state;
	bool			join;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_infos
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
	char			*err_msg;
}				t_infos;

typedef struct s_cmd
{
	bool			is_pipe;
	t_infos			infos;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_cmd;

typedef struct s_env
{
	char			*line;
	char			*var_name;
	char			*var_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_exec
{
	char	*path;
	char	**env_array;
	char	**cmd_and_flags;
}				t_exec;

typedef struct s_data
{
	char	**envp;
	t_env	*env_copy;
	t_env	*env_export;
	char	*line;
	t_token	*token;
	t_cmd	*cmd;
	pid_t	pid;
}				t_data;

#endif