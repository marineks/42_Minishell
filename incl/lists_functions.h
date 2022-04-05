#ifndef LISTS_FUNCTIONS_H
# define LISTS_FUNCTIONS_H

# include "structs.h"

// 05_UTILS // lists_functions --- cmd_list_functions.c
t_cmd	*ft_lstnew_cmd(bool value);
void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new_node);
void	free_matrix(char **tab);
void	ft_lstdelone_cmd(t_cmd *lst, void (*del)(void *));
void	ft_lstclear_cmd(t_cmd **lst, void (*del)(void *));
t_cmd	*ft_lstlast_cmd(t_cmd *cmd);
void	print_cmd(t_cmd *lst);

// 05_UTILS // lists_functions --- env_list_functions.c
t_env	*ft_lstnew_env(char *line, char *name, char *value);
void	ft_lstadd_back_env(t_env **alst, t_env *new_node);
void	ft_lstdelone_env(t_env *lst, void (*del)(void *));
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	print_env(t_env *lst);

// 05_UTILS // lists_functions --- token_list_functions.c
t_token	*ft_lstnew_token(char *str, int type, int state);
void	ft_lstadd_back_token(t_token **alst, t_token *new_node);
void	ft_lstdelone_token(t_token *lst, void (*del)(void *));
void	ft_lstclear_token(t_token **lst, void (*del)(void *));
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);
void	print_token(t_token *lst);

#endif