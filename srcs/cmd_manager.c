/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:43:35 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 23:38:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = split_counter(builtin);
	err_id = 0;
	if (id == 1)
		err_id = echo_builtin(ac, builtin, *env);
	if (id == 3 && (ac == 2 || ac == 3))
		err_id = setenv_builtin(builtin[1], builtin[2], 1, env);
	else if (id == 3 && split_counter(builtin) != 3)
		err_id = SETENV_USG;
	else if (id == 4 && ac == 2)
		err_id = unsetenv_builtin(builtin[1], env);
	else if (id == 4 && ac != 2)
		err_id = UNSETENV_USG;
	if (id == 5)
		err_id = env_builtin(ac, builtin, *env);
	/*
	if (id == 2)
		err_id = cd_builtin(ac, builtin);
	if (id == 6)
		err_id = clear_builtin(ac, builtin);*/
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
//	print_env(env);
}

int		exec_binpath(char **bin, char **env)
{
	struct stat	buf;
	pid_t		pid;

	if (lstat(bin[0], &buf) == -1)
		return (1);
	if (S_ISREG(buf.st_mode) == 1 && access(bin[0], X_OK) == 0)
	{
		if ((pid = fork()) == 0)
			execve(bin[0], bin, env);
		wait(&pid);
	}
	else if (S_ISDIR(buf.st_mode) == 1)
		return (2);
	else if (access(bin[0], X_OK) != 0)
		return (3);
	return (0);
}

int		exec_envpath(char **bin, char **env)
{
	char	**env_path;
	char	*path;
	int		ret;

	if ((path = get_env_path(env)) == NULL || path[0] == '\0')
		ret = split_by_token("./", &env_path, ':');
	else
		ret = split_by_token(path, &env_path, ':');
	if (ret > 0 && find_bin(env_path, bin, env) == 0)
		ft_printf("-minishell: %s: command not found\n", bin[0]);
	else if (ret != 0)
		ft_splitdel(env_path);
	return (0);
}

void	exec_bin(char **bin, char **env)
{
	int	err_id;

	err_id = (is_path(bin[0])) ? exec_binpath(bin, env) :
		exec_envpath(bin, env);
	if (err_id != 0)
		err_handler(err_id, bin[0]);
}

void	cmd_manager(char *cmd, char ***env)
{
	char	**split;
	int		id;

	if (split_by_token(cmd, &split, ' ') > 0)
	{
		id = builtin_id(split[0]);
		(id > 0) ? exec_builtin(split, id, env) : exec_bin(split, *env);
		ft_splitdel(split);
	}
}
