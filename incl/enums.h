/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:57:25 by msanjuan          #+#    #+#             */
/*   Updated: 2022/05/04 12:58:07 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# define PROMPT "🦊🐆\033[1;37m ~ Minishell : \033[0m"
# define ENV_MSG "Pas de bras, pas de chocolat, pas de env, pas de Minishell\n"

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = 2,
	TRUE = 3,
	FALSE = 4
};

enum e_states
{
	DEFAULT,
	SIMPLE,
	DOUBLE
};

enum e_action
{
	BASIC,
	IGNORE,
	DEFAULT_ACTION,
	HEREDOC_MODE
};

enum e_pipesfd
{
	READ,
	WRITE,
};

enum e_tk_types
{
	BLANK = 1,
	WORD,
	VAR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	END
};

#endif