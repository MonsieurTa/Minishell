/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:47:52 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:18:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

char	*get_oldpwd(char *path, char **env)
{
	int	idx;

	idx = -1;
	while (env[++idx] != NULL)
	{
		if (ft_strnequ("OLDPWD=", env[idx], 7) == 1)
			return (env[idx] + 7);
	}
	return (path);
}

int		move_to_dir(char *path, char ***env)
{
	char		cwd[MAX_PATH_LEN];
	struct stat	buf;

	if (path != NULL && ft_strlen(path) == 1 && path[0] == '-')
	{
		path = get_oldpwd(path, *env);
		ft_printf("%s\n", path);
	}
	if (lstat(path, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode) == 1)
		{
			if (access(path, X_OK) == 0)
			{
				setenv_builtin("OLDPWD", getcwd(cwd, sizeof(cwd)), 1, env);
				chdir(path);
				setenv_builtin("PWD", getcwd(cwd, sizeof(cwd)), 1, env);
				return (0);
			}
			return (NO_RIGHT);
		}
		return (NOT_DIR);
	}
	return (NON_EXISTENT);
}

char	*get_hpath(char **env)
{
	int	idx;

	if (env != NULL)
	{
		idx = -1;
		while (env[++idx] != NULL)
		{
			if (ft_strnequ("HOME=", env[idx], 5) == 1)
				return (env[idx] + 5);
		}
	}
	return (NULL);
}

int		cd_builtin(int ac, char **av, char ***env)
{
	char	*path;
	int		err_id;

	err_id = 0;
	path = NULL;
	if (ac == 1 && (path = get_hpath(*env)) != NULL)
		err_id = move_to_dir(path, env);
	else if (ac > 1)
		err_id = move_to_dir(av[1], env);
	if (err_id != 0)
		err_handler(err_id, (path != NULL) ? path : av[1]);
	return (0);
}
