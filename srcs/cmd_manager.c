/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:43:35 by wta               #+#    #+#             */
/*   Updated: 2019/01/11 22:11:57 by wta              ###   ########.fr       */
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
	if (id == 2)
		err_id = cd_builtin(ac, builtin, env);
	if (id == 3 && (ac == 2 || ac == 3))
		err_id = setenv_builtin(builtin[1], builtin[2], 1, env);
	else if (id == 3 && split_counter(builtin) != 3)
		err_id = SETENV_USG;
	else if (id == 4 && ac == 2)
		err_id = unsetenv_builtin(builtin[1], env);
	else if (id == 4 && ac != 2)
		err_id = UNSETENV_USG;
	if (id == 5 && ac > 1)
		err_id = env_builtin(ac, builtin, *env);
	else if (id == 5 && ac == 1)
		print_env(*env);
	if (id == 6)
		exit_builtin();
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
}

int		exec_binpath(char **bin, char **env)
{
	struct stat	buf;
	pid_t		pid;

	if (lstat(bin[0], &buf) == -1)
		return (1);
	if (S_ISREG(buf.st_mode) == 1 && access(bin[0], X_OK) == 0)
	{
		pid = fork();
		signal(SIGINT, sigfork);
		if (pid == 0)
			execve(bin[0], bin, env);
		else if (pid < 0)
			return (FAILFORK);
		wait(&pid);
	}
	else if (S_ISDIR(buf.st_mode) == 1)
		return (IS_DIRECTORY);
	else if (access(bin[0], X_OK) != 0)
		return (NO_RIGHT);
	return (0);
}

int		exec_envpath(char **bin, char **env)
{
	char	**env_path;
	char	*path;

	if ((path = get_env_path(env)) == NULL || path[0] == '\0')
		split_by_token("./", &env_path, ":");
	else
		split_by_token(path, &env_path, ":");
	if (find_bin(env_path, bin, env) == 0)
		ft_printf("-minishell: %s: command not found\n", bin[0]);
	ft_splitdel(env_path);
	return (0);
}

void	exec_bin(char **bin, char **env)
{
	int	err_id;

	print_env(bin);
	err_id = (is_path(bin[0])) ? exec_binpath(bin, env) :
		exec_envpath(bin, env);
	if (err_id != 0)
		err_handler(err_id, bin[0]);
}

void	cmd_manager(char *cmd, char ***env)
{
	char	**split;
	int		idx;
	int		id;

	if (split_by_token(cmd, &split, " \t") > 0)
	{
		idx = -1;
		while (split[++idx] != NULL)
			manager_expand(&split[idx], *env);
		id = builtin_id(split[0]);
		(id > 0) ? exec_builtin(split, id, env) : exec_bin(split, *env);
	}
	ft_splitdel(split);
}
