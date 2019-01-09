/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:43:35 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 07:08:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	err_handler(int err_id, char *path)
{
	(void)err_id;
	(void)path;
}

int		find_bin(char *bin, t_lst *env)
{
	(void)bin;
	(void)env;
	return (1);
}

char	**get_env(t_lst *env)
{
	t_env	*node;
	char	**envcpy;
	int		idx;

	if ((envcpy = (char**)ft_memalloc((sizeof(char*) * env->len))) != NULL)
	{
		node = env->head;
		idx = -1;
		while (node != NULL && ++idx < env->len)
		{
			if ((envcpy[idx] = ft_strdup(node->str)) == NULL)
			{
				ft_splitdel(envcpy);
				return (NULL);
			}
			node = node->next;
		}
	}
	return (envcpy);
}

int		check_path(char *path, int slash, t_lst *env)
{
	struct stat	buf;

	if (slash > 0)
	{
		if (lstat(path, &buf) == -1)
			return (1);
		else
		{
			if (S_ISREG(buf.st_mode) == 1 && access(path, R_OK | X_OK) == 0)
				return (2);
			if (S_ISDIR(buf.st_mode) == 1 && access(path, R_OK | X_OK) == 0)
				return (3);
		}
		return (0);
	}
	return (find_bin(path, env));
}

int		check_err(char *path, t_lst *env)
{
	char	pathcpy[MAX_PATH_LEN];
	int		slash;
	int		idx;
	int		ret;

	ft_bzero((void*)pathcpy, MAX_PATH_LEN);
	ft_strcpy(pathcpy, path);
	idx = -1;
	ret = 0;
	slash = 0;
	while (ret == 0 && pathcpy[++idx] != '\0')
	{
		if (pathcpy[idx] == '/')
		{
			slash += 1;
			pathcpy[idx + 1] = '\0';
			ret = check_path(pathcpy, slash, env);
			pathcpy[idx + 1] = path[idx + 1];
		}
	}
	if (ret != 0 || (ret = check_path(pathcpy, slash, env)) != 0)
		err_handler(ret, path);
	return (ret);
}

void	exec_builtin(char **builtin, int id)
{
	(void)builtin;
	ft_printf("id = %d\n", id);
	return ;
}

void	exec_bin(char **bin, t_lst *env)
{
	pid_t	pid;
	char	**envcpy;
	int		err_id;

	if ((err_id = check_err(bin[0], env)) == 0)
	{
		if ((envcpy = get_env(env)) != NULL)
		{
			if ((pid = fork()) == 0)
				execve(bin[0], bin + 1, envcpy);
		//	else
		//		return ; // TODO memory handling
			wait(&pid);
			ft_splitdel(envcpy);
		}
	}
	else
		err_handler(err_id, bin[0]);
	return ;
}

int		builtin_id(char *str)
{
	if (ft_strequ(str, "echo") == 1)
		return (1);
	else if (ft_strequ(str, "cd") == 1)
		return (2);
	else if (ft_strequ(str, "setenv") == 1)
		return (3);
	else if (ft_strequ(str, "unsetenv") == 1)
		return (4);
	else if (ft_strequ(str, "env") == 1)
		return (5);
	return (0);
}

void	cmd_manager(char *cmd, t_lst *env)
{
	char	**split;
	int		id;

	(void)env;
	if (split_by_token(cmd, &split, ' ') > 0)
	{
		id = builtin_id(split[0]);
		(id > 0) ? exec_builtin(split, id) : exec_bin(split, env);
		ft_splitdel(split);
	}
}
