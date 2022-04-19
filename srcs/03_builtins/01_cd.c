#include "minishell.h"

static int	too_many_arg_err(void)
{
	ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	g_exit_status = 1;
	return (g_exit_status);
}

static char	*find_home_path(t_env *env)
{
	char	*path;
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->var_name, "HOME") == SUCCESS)
			break;
		tmp = tmp->next;
	}
	path = ft_strdup(tmp->var_value);
	if (!path)
		return (NULL);
	return (path);
}

static int	display_chdir_errno(char *strerror, char *flag)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(flag, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_exit_status = 1;
	return (g_exit_status);
}

void	update_all_pwds(t_env **env)
{
	char	*tmp_pwd;
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
	{
		if (ft_strcmp("PWD", tmp->var_name) == SUCCESS)
			break;
		tmp = tmp->next;
	}
	tmp_pwd = ft_strdup(tmp->var_value);
	free(tmp->var_value);
	tmp->var_value = getcwd(NULL, 0);
	tmp = *env;
	while (tmp->next)
	{
		if (ft_strcmp("OLDPWD", tmp->var_name) == SUCCESS)
			break;
		tmp = tmp->next;
	}
	free(tmp->var_value);
	tmp->var_value = ft_strdup(tmp_pwd);
	free(tmp_pwd);
}

/**
 * @brief Change the current repertory.
 * 
 * 		Steps :
 * 		1) Chdir requires a path. Find the right path (cmd->flags or home path)
 * 		2) Execute chdir and manage the potential errors
 * 		3) Update the env
 * 
 * @param cmd the current command issued
 * @param env the current env
 * @return int the exit status code
 */
int	change_directory(t_cmd *cmd, t_env **env)
{
	char *path;

	if (cmd->infos.flags)
	{
		if (cmd->infos.flags[1])
			return (too_many_arg_err());
		if (ft_strcmp(cmd->infos.flags[0], "~") == SUCCESS)
			path = find_home_path(*env);
		else
			path = ft_strdup(cmd->infos.flags[0]);
	}
	else
		path = find_home_path(*env);
	if (chdir(path) != 0)
	{
		cmd->infos.err_msg = ft_strdup(strerror(errno));
		return (display_chdir_errno(cmd->infos.err_msg, cmd->infos.flags[0]));
	}
	free(path);
	update_all_pwds(env);
	return (g_exit_status);
}